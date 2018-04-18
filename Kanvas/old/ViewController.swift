//
//  ViewController.swift
//  Kanvas
//
//  Created by Maninder Singh on 31/01/18.
//  Copyright © 2018 Maninder Singh. All rights reserved.
//

import UIKit
import SwitchFramework
import ReplayKit

class ViewController: UIViewController {
    
    var doubleTapGestureRecognizer = UITapGestureRecognizer()
    var longPressGestureRecognizer = UILongPressGestureRecognizer()
    var rotationGestureRecognizer = UIRotationGestureRecognizer()
    var pinchGestureRecognizer = UIPinchGestureRecognizer()
    
    var cameraPosition : AVCaptureDevice.Position?
    var captureSession = AVCaptureSession()
    
    var audioDeviceInput : AVCaptureDeviceInput?
    var videoSessionQueue : DispatchQueue?
    var audioSessionQueue : DispatchQueue?
    var videoDataOutput = AVCaptureVideoDataOutput()
    var audioDataOutput = AVCaptureAudioDataOutput()
    var AudioPlayer = AVAudioPlayer()
    
    var  trackingEngine : SWTrackingEngine?
    var scnView: SCNView!
    let record = RPScreenRecorder.shared()

    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupEngines()
    }
    

    func setupEngines() {
        let base64Sig = "MEQCIBR5h9NM5ilJoSvYpPBtfmEP68S2r4MerZ2DaENR2nH3AiACICoKhJYzIExBh8LMARQ9e91LM5rYQMEsiONxSKphGw=="
        let client_id = "58c8d069014fdd2ea60c826c"
        let verified: Bool = SwitchFramework.initialize(withClientID: client_id, signature: base64Sig)
        if verified{
            setupView()
            setupCamera()
        }
        else{
            print("SDK Error : Not initialized")
        }
    }
    
    func setupView(){
        self.trackingEngine = SWTrackingEngine.init()
        self.scnView = self.trackingEngine?.scnView(withFrame: CGRect(x: 0, y: 0, width: self.view.bounds.width, height: self.view.bounds.height - 100))
        self.scnView.isJitteringEnabled = false
        //self.scnView.showsStatistics = true
        self.view.addSubview(self.scnView)
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
                        print("not granted access to \(mediaType)")
                    }
                })
            })
        }
    }

    
    @IBAction func changeCam(_ sender: Any) {
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
                print("Device erro : \(error.localizedDescription) ")
            }
        }
        videoSessionQueue = DispatchQueue(label: "video session queue")
        videoDataOutput.setSampleBufferDelegate(self, queue: videoSessionQueue)
        videoDataOutput.alwaysDiscardsLateVideoFrames = true
        videoDataOutput.videoSettings = [(kCVPixelBufferPixelFormatTypeKey as String): kCVPixelFormatType_32BGRA]
        let array = videoDataOutput.availableVideoPixelFormatTypes
        //videoDataOutput.availableVideoCVPixelFormatTypes()
        print("available pixel format types: \(String(describing: array))")
        captureSession.addOutput(videoDataOutput)
        let connection = videoDataOutput.connection(with: .video)
        if connection != nil {
            if (connection?.isVideoMirroringSupported)! && cameraPosition == .front {
                print("isVideoMirroringSupported")
                connection?.isVideoMirrored = true
            }else{
                print("No VideoMirroringSupported")
                connection?.isVideoMirrored = false
            }
            connection?.videoOrientation = .portrait
        }
        _ = AVAudioSession.sharedInstance()

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

    
        
//        record.startRecording { (error) in
//            print("**********************error****************")
//        }
    }
    

    
    func pngFilePath(_ name: String) -> String {
//        let AssortedMusics = NSURL(fileURLWithPath: Bundle.main.path(forResource: "Baatein", ofType: "mp3")!)
//        AudioPlayer = try! AVAudioPlayer(contentsOf: AssortedMusics as URL)
//        AudioPlayer.prepareToPlay()
//        AudioPlayer.numberOfLoops = -1
//        AudioPlayer.play()
        
        
        let asssPath = String(format:"Assets/%@",name)
        let arr = Bundle.main.paths(forResourcesOfType: "jpg", inDirectory: asssPath, forLocalization: nil)
        for arr1 in arr{
            let maskAttachable = SWMaskAttachable.init(imageFilePath: arr1, withScale: 0.4)
            trackingEngine?.add(maskAttachable)
        }
        return ""
//        let pngFilePath: String? = Bundle.main.path(forResource: asssPath, ofType: "jpg")
//        return pngFilePath ?? ""
    
    }

    
    func pngFilePath1(_ name: String) -> String{
        let scnFilePath: String? = Bundle.main.path(forResource: "Assets/Cap/\(name)", ofType: "png")
        return scnFilePath ?? ""
    }
    
    func scnFilePath(_ name: String) -> String {
        let scnFilePath: String? = Bundle.main.path(forResource: "Assets/\(name)/\(name)", ofType: "obj")
        return scnFilePath ?? ""
    }
    
    func newP(_ name : String) -> String{
        let scnFilePath: String? = Bundle.main.path(forResource: "Assets/\(name)/\(name)", ofType: "png")
        return scnFilePath ?? ""
    }
    
    @IBAction func button(_ sender: Any) {
                let AssortedMusics = NSURL(fileURLWithPath: Bundle.main.path(forResource: "Assets/Cap/baatein", ofType: "mp4")!)
                AudioPlayer = try! AVAudioPlayer(contentsOf: AssortedMusics as URL)
                AudioPlayer.prepareToPlay()
                AudioPlayer.numberOfLoops = -1
                AudioPlayer.play()
//        let maskAttachable1 = SWMaskAttachable(imageFilePath: pngFilePath1("masker"), withScale: 1)
//        trackingEngine?.add(maskAttachable1)
        let maskAttachable = SWStickerAttachable.init()
        maskAttachable.loadObjs(atPaths: [scnFilePath("Cap")])
        maskAttachable.loadImages(atPaths: [newP("Cap")])

        //trackingEngine?.add(maskAttachable1)
        maskAttachable.trackedVertex = 9
        maskAttachable.currentScale = 14
        maskAttachable.fps = 15
        trackingEngine?.add(maskAttachable)

        
        
//
    

//        let attachables = SWStickerAttachable.attachables(fromSCNFilePath: scnFilePath("CYBORG"))
//        for attachable in attachables! {
//            if let attact = attachable as? SWStickerAttachable{
//                attact.currentScale = 0.6
//            }
//            if let att = attachable as? SWEnvironmentAttachable{
//                att.loadScene(atPath: self.scnFilePath("CYBORG"))
//            }
//        }
//        trackingEngine?.add(attachables)
    }
    
    @IBAction func saveImageBUtton(_ sender: Any) {
       
//        record.stopRecording { (previewVC, error) in
//            if let prvc = previewVC{
//                prvc.previewControllerDelegate = self
//                self.present(prvc, animated: true, completion: nil)
//
//            }
//            if error != nil{
//                print("**********************\(error)****************")
//            }
//        }
//        let Image = self.scnView.snapshot()
//        UIImageWriteToSavedPhotosAlbum(Image, nil, nil, nil)
    }
}


extension ViewController: AVCaptureVideoDataOutputSampleBufferDelegate, RPPreviewViewControllerDelegate{
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        let pixelBuffer: CVImageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)!
        CVPixelBufferLockBaseAddress(pixelBuffer, CVPixelBufferLockFlags(rawValue: 0))
        DispatchQueue.main.sync(execute: {() -> Void in
            _  = self.trackingEngine?.trackingModel(forCVPixelBufferRef: pixelBuffer, renderObjects: true)
          //  print("DOne")
        })
        CVPixelBufferUnlockBaseAddress(pixelBuffer, CVPixelBufferLockFlags(rawValue: 0))
    }
    
    func previewControllerDidFinish(_ previewController: RPPreviewViewController) {
        dismiss(animated: true, completion: nil)
    }
}


