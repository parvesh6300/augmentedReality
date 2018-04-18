//
//  Constants.h
//  SwitchSceneKit
//
//  Created by Tony Cheng on 10/27/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#ifndef SWConstants_h
#define SWConstants_h

#ifdef DEBUG
#	define SWLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#	define SWLog(...)
#endif

#endif /* Constants_h */
