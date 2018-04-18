//
//  newVCViewController.swift
//  Kanvas
//
//  Created by Maninder Singh on 02/02/18.
//  Copyright © 2018 Maninder Singh. All rights reserved.
//

import UIKit
import AVFoundation

class newVCViewController: UIViewController,AVCaptureVideoDataOutputSampleBufferDelegate {

    @IBOutlet weak var filteredImage: UIImageView!
    
    var frontCamera : AVCaptureDevice?
    var backCamera : AVCaptureDevice?
    var currentCamera : AVCaptureDevice?
    var photoOutput : AVCapturePhotoOutput?
    var videoOutput : AVCaptureVideoDataOutput?
    let context = CIContext()
    var capturePreviewLayer: AVCaptureVideoPreviewLayer?
    var captureSession = AVCaptureSession()
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setUpCameraSession()
        setupDevice()
        setupInputOutput()
       // setupPreviewLayer()
        StartSession()
    }

    
   
    
    func setUpCameraSession(){
        captureSession.sessionPreset = AVCaptureSession.Preset.vga640x480
    }

    func setupDevice(){
        let deviceDiscoverySession = AVCaptureDevice.DiscoverySession(deviceTypes: [.builtInWideAngleCamera], mediaType: AVMediaType.video, position: .unspecified)
        let devices = deviceDiscoverySession.devices
        for device in devices{
            if device.position == .back{
                backCamera = device
            }else if device.position == .front{
                frontCamera = device
            }
        }
        currentCamera = frontCamera
    }
    
    func setupInputOutput(){
        do{
            let captureDevice = try AVCaptureDeviceInput(device: currentCamera!)
            captureSession.addInput(captureDevice)
            let videoOutput = AVCaptureVideoDataOutput()
            
            videoOutput.setSampleBufferDelegate(self, queue: DispatchQueue(label: "sample buffer delegate", attributes: []))
            if captureSession.canAddOutput(videoOutput) {
                captureSession.addOutput(videoOutput)
            }
            //for photo
            /*
            if #available(iOS 11.0, *) {
                let capturePhotoSettings = AVCapturePhotoSettings(format: [AVVideoCodecKey: AVVideoCodecType.jpeg])
                photoOutput?.setPreparedPhotoSettingsArray([capturePhotoSettings], completionHandler: nil)
            } else {
                // Fallback on earlier versions
            }*/
        }catch{
            print(error)
        }
    }
    
    func setupPreviewLayer(){
        capturePreviewLayer = AVCaptureVideoPreviewLayer(session: captureSession)
        capturePreviewLayer?.videoGravity = .resizeAspectFill
        capturePreviewLayer?.connection?.videoOrientation = .portrait
        capturePreviewLayer?.frame = self.view.frame
        self.view.layer.insertSublayer(capturePreviewLayer!, at: 0)
    }
    
    func StartSession(){
        captureSession.startRunning()
    }
    
    
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        connection.videoOrientation = .portrait
        let videoOutput = AVCaptureVideoDataOutput()
        videoOutput.setSampleBufferDelegate(self, queue: DispatchQueue.main)
        
        let comicEffect = CIFilter(name: "CIPhotoEffectChrome")
        
        let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)
        let cameraImage = CIImage(cvImageBuffer: pixelBuffer!)
        
        comicEffect!.setValue(cameraImage, forKey: kCIInputImageKey)
        
        let cgImage = self.context.createCGImage(comicEffect!.outputImage!, from: cameraImage.extent)!
        
        DispatchQueue.main.async {
            let filteredImage = UIImage(cgImage: cgImage)
            self.filteredImage.image = filteredImage
        }
    }

}





