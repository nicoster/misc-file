//
//  MovieInfoController.h
//  wirelessDemo
//
//  Created by Max Qian on 1/9/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MovieInfo.h"

@interface MovieInfoController : UIViewController{
    
    UIImageView * _moviepic;
    UILabel * _moviename;
    UILabel * _score;
    UILabel * _director;
    UILabel * _performers;
    UILabel * _duration;

    
    UITextView * _descp;
    UITextView * _comments;
    
    MovieInfo * _movieinfo;
}

@property (retain, nonatomic) IBOutlet UIImageView *moviepic;
@property (retain, nonatomic) IBOutlet UILabel *moviename;
@property (retain, nonatomic) IBOutlet UILabel *moviescore;
@property (retain, nonatomic) IBOutlet UILabel *director;
@property (retain, nonatomic) IBOutlet UILabel *performers;
@property (retain, nonatomic) IBOutlet UILabel *duration;
//- (IBAction)showprevue:(id)sender;
@property (retain, nonatomic) IBOutlet UITextView *descp;
@property (retain, nonatomic) IBOutlet UITextView *comments;

@property(retain, nonatomic) MovieInfo * movieinfo;

@end
