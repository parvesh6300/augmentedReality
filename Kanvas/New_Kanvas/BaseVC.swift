//
//  BaseVC.swift
//  FriendsApp
//
//  Created by Maninder Singh on 21/10/17.
//  Copyright © 2017 ManinderBindra. All rights reserved.
//

import UIKit

class BaseVC: UIViewController {
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    //MARK: *************   Show Alert   ***************
    func showAlert(message: String?, title:String = "Alert!", otherButtons:[String:((UIAlertAction)-> ())]? = nil, cancelTitle: String = "Okay", cancelAction: ((UIAlertAction)-> ())? = nil) {
        let newTitle = title.capitalized
        let newMessage = message
        let alert = UIAlertController(title: newTitle, message: newMessage, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: cancelTitle, style: .cancel, handler: cancelAction))
        
        if otherButtons != nil {
            for key in otherButtons!.keys {
                alert.addAction(UIAlertAction(title: key, style: .default, handler: otherButtons![key]))
            }
        }
        present(alert, animated: true, completion: nil)
    }
    
    func showErrorMessage(error: NSError?, cancelAction: ((UIAlertAction)-> ())? = nil) {
        var title = "Error"
        var message = "Something Went Wrong"
        if error != nil {
            title = error!.domain
            message = error!.userInfo["message"] as? String ?? ""
        }
        let newTitle = title.capitalized
        let newMessage = message.capitalized
        let alert = UIAlertController(title: newTitle, message: newMessage, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Okay", style: .cancel, handler: cancelAction))
        present(alert, animated: true, completion: nil)
    }
    
}

