//
//  MovieInfoController.h
//  wirelessDemo
//
//  Created by Max Qian on 1/9/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MovieInfo.h"
#import <MediaPlayer/MediaPlayer.h>

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
    
    UIButton * _btn;
    
    MPMoviePlayerViewController * _play;
}

@property (retain, nonatomic) IBOutlet UIImageView *moviepic;
@property (retain, nonatomic) IBOutlet UILabel *moviename;
@property (retain, nonatomic) IBOutlet UILabel *moviescore;
@property (retain, nonatomic) IBOutlet UILabel *director;
@property (retain, nonatomic) IBOutlet UILabel *performers;
@property (retain, nonatomic) IBOutlet UILabel *duration;

-(IBAction)showprevue:(id)sender;

@property (retain, nonatomic) IBOutlet UITextView *descp;
@property (retain, nonatomic) IBOutlet UITextView *comments;

@property (retain, nonatomic) IBOutlet UIButton * btn;

@property(retain, nonatomic) MovieInfo * movieinfo;

@property(retain, nonatomic) MPMoviePlayerViewController * play;

-(id) initWithInfo:(MovieInfo *)p;

@end
