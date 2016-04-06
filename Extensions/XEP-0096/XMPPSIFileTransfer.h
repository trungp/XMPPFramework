//
//  MultiCast.h
//  TrustTextXMPP
//
//  Created by Min Kwon on 3/11/13.
//  Copyright (c) 2013 Min Kwon. All rights reserved.
//
//  Implementation of http://xmpp.org/extensions/xep-0096.html


#import <Foundation/Foundation.h>
#import "XMPP.h"
#import "TURNSocket.h"
#import <UIKit/UIKit.h>

@class GCDAsyncSocket;

typedef enum {
    kXMPPSIFileTransferStateNone,
    kXMPPSIFileTransferStateSending,
    kXMPPSIFileTransferStateReceiving
} XMPPSIFileTransferState;

typedef enum {
    kXMPPSIFileTransferMimeTypeNone,
    kXMPPSIFileTransferMimeTypeJPG,
    kXMPPSIFileTransferMimeTypePNG,
    kXMPPSIFileTransferMimeTypeGIF,
    kXMPPSIFileTransferMimeTypeMOV
} XMPPSIFileTransferMimeType;

@interface XMPPSIFileTransfer : XMPPModule<TURNSocketDelegate, GCDAsyncSocketDelegate> {
    TURNSocket *turnSocket;
    XMPPSIFileTransferState state;
    NSMutableData *receivedData;
    XMPPSIFileTransferMimeType mimeType;
    XMPPJID *senderJID;
}


- (void)initiateFileTransferTo:(XMPPJID*)to withData:(NSData*)data andFileName:(NSString*)fileName type:(NSString *)type;

- (void)initiateFileTransferTo:(XMPPJID*)to withData:(NSData*)data andFileName:(NSString*)fileName;

/**
 * We need to keep track of the sid (the id of the <s> element. When a negotation is received,
 * we will either receive a set iq or send a set iq with a particular sid.  This sid is used
 * again when the file is sent or received, and must match. 
**/
@property (nonatomic, strong) NSString *sid;

@end



@protocol XMPPSIFileTransferDelegate <NSObject>
@optional
- (void)fileTransfer:(XMPPSIFileTransfer*)xmppFileTransfer receivingImage:(NSString*)fileName progress:(CGFloat)progress from:(XMPPJID*)from;
- (void)fileTransfer:(XMPPSIFileTransfer*)xmppFileTransfer receivedImage:(NSString*)fileName data:(NSData*)image from:(XMPPJID*)from;
- (void)fileTransfer:(XMPPSIFileTransfer*)xmppFileTransfer didFailReceiveImage:(NSString*)fileName from:(XMPPJID*)from;
- (void)fileTransfer:(XMPPSIFileTransfer*)xmppFileTransfer sendingImage:(NSString*)fileName progressData:(NSData*)data to:(XMPPJID*)to;
- (void)fileTransfer:(XMPPSIFileTransfer*)xmppFileTransfer didSendImage:(NSString*)fileName data:(NSData*)image to:(XMPPJID*)to;
- (void)fileTransfer:(XMPPSIFileTransfer*)xmppFileTransfer didFailSendImage:(NSString*)fileName to:(XMPPJID*)to;
@end
