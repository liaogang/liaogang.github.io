---
layout: post
title:  "Test cplusplus code"
date:   2014-08-07 
categories: st
---


    -(void)flashMessage:(NSString*)t
	{
		_labelMessage.text=t;
		
		[NSObject cancelPreviousPerformRequestsWithTarget:self];
		[self performSelector:@selector(clearMessage) withObject:nil afterDelay:5];
				
		[[[UIAlertView alloc] initWithTitle:t message:NSLocalizedString(@"Verify your network connectivity(visit google if you are using chromecast.)\nAnd try to cast again \n Or reconnect to the device or click button \"stop all\"",nil) delegate:nil cancelButtonTitle:nil otherButtonTitles:NSLocalizedString(@"ok", nil), nil] show];
	
	}
