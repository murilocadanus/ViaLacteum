//
//  AudioPlayer.m
//  ViaLacteum
//
//  Created by Marlus Costa on 28/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "AudioPlayer.h"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>


@implementation AudioPlayer

- (id)init
{
    self = [super init];
    if (self) {
        NSSound *mySound = [[NSSound alloc] initWithContentsOfFile:@"resources/Invasores.wav" byReference:YES]; 
        [mySound play];
    }
     
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

@end
