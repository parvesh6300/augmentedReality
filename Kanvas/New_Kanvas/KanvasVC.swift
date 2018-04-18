//
//  KanvasVC.swift
//  Kanvas
//
//  Created by Maninder Singh on 06/02/18.
//  Copyright © 2018 Maninder Singh. All rights reserved.
//

import UIKit
import ARKit
import SwitchFramework

class KanvasVC: BaseVC {
    
    //MARK:- IBOutlets
    @IBOutlet weak var clickButton: UIButton!
    
    @IBOutlet weak var collectionView: UICollectionView!
    @IBOutlet weak var camView: UIView!
    @IBOutlet weak var filteredImage: UIImageView!
    
    //MARK:- Variables
    let base64Sig = "MEQCIBR5h9NM5ilJoSvYpPBtfmEP68S2r4MerZ2DaENR2nH3AiACICoKhJYzIExBh8LMARQ9e91LM5rYQMEsiONxSKphGw=="
    let client_id = "58c8d069014fdd2ea60c826c"
    let itemsArr = [#imageLiteral(resourceName: "BEAR.png"),#imageLiteral(resourceName: "Mono"),#imageLiteral(resourceName: "Chrome"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone"),#imageLiteral(resourceName: "SepiaTone")]
    var previousOffset = CGFloat()
    var currentPage = 0
    
    var scnView: SCNView!
    let context = CIContext()
    var scrollToIndex : IndexPath?
    
    var typFilter = "simple"
    
    var centerCell = UICollectionViewCell()
    var cellIsInCenter = false
    var myIndexPath = IndexPath()
    var horizontalCellSize = CGSize(width: 50, height: 50)
    var horizontalLargeCellSize = CGSize(width: 80, height: 80)
    
    //Tacking Engine
    var  trackingEngine : SWTrackingEngine?
    
    //Video
    var cameraPosition : AVCaptureDevice.Position?
    var captureSession = AVCaptureSession()
    
    var audioDeviceInput : AVCaptureDeviceInput?
    var videoSessionQueue : DispatchQueue?
    var audioSessionQueue : DispatchQueue?
    var videoDataOutput = AVCaptureVideoDataOutput()
    var audioDataOutput = AVCaptureAudioDataOutput()
    var AudioPlayer = AVAudioPlayer()
    
    
    //MARK:- VC Methods
    override func viewDidLoad() {
        super.viewDidLoad()
        self.clickButton.layer.cornerRadius = 35
        self.clickButton.layer.borderColor = UIColor.white.cgColor
        self.clickButton.layer.borderWidth = 5
        collectionView.dataSource = self
        collectionView.delegate = self
        setupEngines()
    }
    
    //MARK:- IBActions
    @IBAction func flipCameraButtonAction(_ sender: Any) {
        captureSession.stopRunning()
        if let inputs = captureSession.inputs as? [AVCaptureDeviceInput]{
            for input in inputs{
                captureSession.removeInput(input)
            }
        }
        let outPuts = captureSession.outputs
        for outPut in outPuts{
            captureSession.removeOutput(outPut)
        }
        
        captureSession.sessionPreset = .vga640x480
        if cameraPosition == .front{
            initCapture(camera: .back)
        }else{
            initCapture(camera: .front)
        }
    }
    
    
    //MARK:- Custom Methods
    
    func setupEngines() {
        let verified = SwitchFramework.initialize(withClientID: client_id, signature: base64Sig)
        if verified{
            setupView()
            setupCamera()
        }
        else{
            self.showAlert(message: "SDK Error : Not initialized")
        }
    }
    
    func setupView(){
        self.trackingEngine = SWTrackingEngine.init()
        self.scnView = self.trackingEngine?.scnView(withFrame: CGRect(x: 0, y: 0, width: UIScreen.main.bounds.width, height: UIScreen.main.bounds.height))
        
        self.camView.addSubview(self.scnView)
    }
    
    func setupCamera() {
        let mediaType = AVMediaType.video.rawValue
        let authStatus = AVCaptureDevice.authorizationStatus(for: AVMediaType(mediaType))
        if authStatus == .authorized {
            initCapture(camera: .front)
        }
        else {
            AVCaptureDevice.requestAccess(for: AVMediaType(mediaType), completionHandler: {(_ granted: Bool) -> Void in
                DispatchQueue.main.async(execute: {() -> Void in
                    if granted {
                        // UI updates as needed
                        self.initCapture(camera: .front)
                    }
                    else {
                        // UI updates as needed
                        self.showAlert(message: "Access not granted to \(mediaType)")
                    }
                })
            })
        }
    }
    
    
    func initCapture(camera : AVCaptureDevice.Position){
        cameraPosition = camera
        captureSession.beginConfiguration()
        captureSession.sessionPreset = .vga640x480
        let discoverySession = AVCaptureDevice.DiscoverySession(deviceTypes: [.builtInWideAngleCamera], mediaType: .video, position: cameraPosition!)
        let devices = discoverySession.devices
        if devices.count > 0{
            let device = devices.first
            do{
                let newVideoInput = try AVCaptureDeviceInput(device: device!)
                captureSession.addInput(newVideoInput)
            }catch(let error){
                self.showAlert(message: "Device error : \(error.localizedDescription)")
            }
        }
        videoSessionQueue = DispatchQueue(label: "video session queue")
        videoDataOutput.setSampleBufferDelegate(self, queue: videoSessionQueue)
        videoDataOutput.alwaysDiscardsLateVideoFrames = true
        videoDataOutput.videoSettings = [(kCVPixelBufferPixelFormatTypeKey as String): kCVPixelFormatType_32BGRA]
        let array = videoDataOutput.availableVideoCodecTypes
        print("available pixel format types: \(String(describing: array))")
        captureSession.addOutput(videoDataOutput)
        let connection = videoDataOutput.connection(with: .video)
        connection?.videoOrientation = .portrait
        if connection != nil {
            if (connection?.isVideoMirroringSupported)! && cameraPosition == .front {
                connection?.isVideoMirrored = true
            }else{
                connection?.isVideoMirrored = false
            }
        }
        audioSessionQueue = DispatchQueue(label: "audio session queue")
        let audioDevice = AVCaptureDevice.default(for: .audio)
        do{
            audioDeviceInput = try AVCaptureDeviceInput(device: audioDevice!)
            if captureSession.canAddInput(audioDeviceInput!){
                captureSession.addInput(audioDeviceInput!)
            }
            else {
                print("failed to add input to capture session: \(String(describing: audioDeviceInput))")
            }
        }catch(let error){
            print("audio device error: \(error.localizedDescription)")
        }
        audioDataOutput.setSampleBufferDelegate(nil, queue: audioSessionQueue)
        if captureSession.canAddOutput(audioDataOutput){
            captureSession.addOutput(audioDataOutput)
        }
        captureSession.commitConfiguration()
        captureSession.startRunning()
    }
}



extension KanvasVC: AVCaptureVideoDataOutputSampleBufferDelegate{
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        
        if typFilter == "CIPhotoEffectMono" || typFilter == "CIPhotoEffectChrome" || typFilter == "CISepiaTone" || typFilter == "simple"{
            
            setCIFilters(connection: connection, sampleBuffer: sampleBuffer, FilterName: typFilter)
        }else if typFilter == "cap"{
            
            let pixelBuffer: CVImageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)!
            CVPixelBufferLockBaseAddress(pixelBuffer, CVPixelBufferLockFlags(rawValue: 0))
            DispatchQueue.main.sync(execute: {() -> Void in
                self.filteredImage.isHidden = true
                _ = self.trackingEngine?.trackingModel(forCVPixelBufferRef: pixelBuffer, renderObjects: true)
            })
            CVPixelBufferUnlockBaseAddress(pixelBuffer, CVPixelBufferLockFlags(rawValue: 0))
        }
    }
}

extension KanvasVC : UICollectionViewDataSource, UICollectionViewDelegate,UICollectionViewDelegateFlowLayout {
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return itemsArr.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "FiltersCell", for: indexPath) as! FiltersCell
        cell.imageView.image = itemsArr[indexPath.item]
        return cell
    }
    
    
//    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
//        if collectionView == collectionView {
//            let size = CGSize(width: collectionView.bounds.width, height: collectionView.bounds.height)
//            return size
//        }
//        let point = CGPoint(x: self.view.frame.size.width/2.0, y:35 )
//        //or you can try this code also
//        //let point = CGPoint(x: UIScreen.main.bounds.width/2, y:35 )
//        print(point)
//       // let centerPoint = CGPoint(x: ui, y: <#T##CGFloat#>)
//        let centerIndex = self.collectionView.indexPathForItem(at: point)
//        if indexPath.item == centerIndex?.item {
//            return CGSize(width: 70, height: 70)
//        }
//        return CGSize(width: 50, height: 50)
//
//    }

    
    

    
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, insetForSectionAt section: Int) -> UIEdgeInsets{
        
        return UIEdgeInsets(top: 0, left: UIScreen.main.bounds.width/2 - 35, bottom: 0, right: UIScreen.main.bounds.width/2 - 35)
    }
    
    
    func pngFilePath(_ name: String) -> String {
        //        let AssortedMusics = NSURL(fileURLWithPath: Bundle.main.path(forResource: "Baatein", ofType: "mp3")!)
        //        AudioPlayer = try! AVAudioPlayer(contentsOf: AssortedMusics as URL)
        //        AudioPlayer.prepareToPlay()
        //        AudioPlayer.numberOfLoops = -1
        //        AudioPlayer.play()
        let pngFilePath: String? = Bundle.main.path(forResource: "Assets/\(name)/\(name)", ofType: "png")
        return pngFilePath ?? ""
    }
    
    func scrollViewDidEndDecelerating(_ scrollView: UIScrollView) {
        guard let index = scrollToIndex else {
            return
        }
        self.collectionView.scrollToItem(at: index, at: .centeredHorizontally , animated: true)
    }
    
    
    func scrollViewWillEndDragging(_ scrollView: UIScrollView, withVelocity velocity: CGPoint, targetContentOffset: UnsafeMutablePointer<CGPoint>) {
        let closestCell = self.collectionView.visibleCells
        let center  = ((closestCell.first?.center.x)! + (closestCell.last?.center.x)!)/2
        scrollToIndex = self.collectionView.indexPathForItem(at: CGPoint(x: center, y: 5))
        
    }
    
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        self.collectionView.scrollToItem(at: indexPath, at: .centeredHorizontally, animated: true)
        if indexPath.row == 0{
            typFilter = "cap"
            let maskAttachable = SWMaskAttachable.init(imageFilePath: pngFilePath("BEAR"), withScale: 0.4)
            trackingEngine?.add(maskAttachable)
            self.camView.addSubview(self.scnView)
        }
        if indexPath.row == 1{
            typFilter = "CIPhotoEffectChrome"
        }
        if indexPath.row == 2{
            typFilter = "CISepiaTone"
        }
        if indexPath.row == 3{
            typFilter = "CIPhotoEffectMono"
        }
        
    }
    
    func setCIFilters(connection: AVCaptureConnection, sampleBuffer: CMSampleBuffer, FilterName: String){
        connection.videoOrientation = .portrait
        let videoOutput = AVCaptureVideoDataOutput()
        videoOutput.setSampleBufferDelegate(self, queue: DispatchQueue.main)
        if FilterName == "CIPhotoEffectChrome"{
            let comicEffect = CIFilter(name: "CIPhotoEffectChrome")
            let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)
            let cameraImage = CIImage(cvImageBuffer: pixelBuffer!)
            
            comicEffect!.setValue(cameraImage, forKey: kCIInputImageKey)
            
            let cgImage = self.context.createCGImage(comicEffect!.outputImage!, from: cameraImage.extent)!
            
            DispatchQueue.main.async {
                self.filteredImage.isHidden = false
                self.scnView.removeFromSuperview()
                let filteredImage = UIImage(cgImage: cgImage)
                self.filteredImage.image = filteredImage
            }
        }
        
        if FilterName == "CISepiaTone"{
            let comicEffect = CIFilter(name: "CISepiaTone")
            let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)
            let cameraImage = CIImage(cvImageBuffer: pixelBuffer!)
            
            comicEffect!.setValue(cameraImage, forKey: kCIInputImageKey)
            
            let cgImage = self.context.createCGImage(comicEffect!.outputImage!, from: cameraImage.extent)! 
            
            DispatchQueue.main.async {
                self.filteredImage.isHidden = false
                self.scnView.removeFromSuperview()
                let filteredImage = UIImage(cgImage: cgImage)
                self.filteredImage.image = filteredImage
            }
        }
        if FilterName == "CIPhotoEffectMono"{
            let comicEffect = CIFilter(name: "CIPhotoEffectMono")
            let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)
            let cameraImage = CIImage(cvImageBuffer: pixelBuffer!)
            
            comicEffect!.setValue(cameraImage, forKey: kCIInputImageKey)
            
            let cgImage = self.context.createCGImage(comicEffect!.outputImage!, from: cameraImage.extent)!
            
            DispatchQueue.main.async {
                self.filteredImage.isHidden = false
                self.scnView.removeFromSuperview()
                let filteredImage = UIImage(cgImage: cgImage)
                self.filteredImage.image = filteredImage
            }
        }
        
        if FilterName == "simple"{
            //let comicEffect = CIFilter(name: "CIPhotoEffectMono")
            let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)
            let cameraImage = CIImage(cvImageBuffer: pixelBuffer!)
            //  comicEffect!.setValue(cameraImage, forKey: kCIInputImageKey)
            let cgImage = self.context.createCGImage(cameraImage, from: cameraImage.extent)
            
            DispatchQueue.main.async {
                self.filteredImage.isHidden = false
                self.scnView.removeFromSuperview()
                let filteredImage = UIImage(cgImage: cgImage!)
                self.filteredImage.image = filteredImage
            }
        }
    }
}


