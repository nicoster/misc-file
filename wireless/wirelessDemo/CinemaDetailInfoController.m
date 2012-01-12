//
//  CinemaDetailInfoController.m
//  wirelessDemo
//
//  Created by Max Qian on 1/11/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "CinemaDetailInfoController.h"
#import "MovieInfo.h"


@implementation CinemaDetailInfoController
@synthesize cinemaname = _cinemaname;
@synthesize cinemaid = _cinemaid;
@synthesize cinemaDetailtable = _cinemaDetailtable;

-(id)initWithCinemaId:(NSNumber *)cinemaid
{
    self = [super initWithNibName:nil bundle:nil];
    if(self)
    {
        self.cinemaid = cinemaid;
    }
    
    for (CinemaInfo* p in [DataStore SharedDataStore].cinema_info_array) 
    {
        if([p.cinemaid intValue] == [self.cinemaid intValue])
        {
            _cinemainfo = p;
            break;
        }
    }

    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self.cinemaname setText:_cinemainfo.cinemaname];
}

- (void)viewDidUnload
{
    [self setCinemaname:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)dealloc {
    [_cinemaname release];
    [super dealloc];
}

-(NSString *)getStringWithIndex:(NSIndexPath *)indexPath{
    
    NSString * strCell;
    switch (indexPath.section) {
        case 0:
            switch (indexPath.row) {
                case 0:
                    strCell = [NSString stringWithFormat:@"所在地区 : %@", _cinemainfo.area];
                    break;
                case 1:
                    strCell = [NSString stringWithFormat:@"营业时间 : %@", _cinemainfo.opentime];
                    break;
                case 2:
                    strCell = [NSString stringWithFormat:@"电话 : %@", _cinemainfo.telphone];
                default:
                    break;
            }
            break;
        case 1:
            switch (indexPath.row) {
                case 0:
                    strCell = [NSString stringWithFormat:@"设施 : %@", _cinemainfo.facilities];
                    break;
                case 1:
                    strCell = [NSString stringWithFormat:@"环境 : %@", _cinemainfo.entplace];                
                default:
                    break;
            }
            break;
        case 2:
            switch (indexPath.row) {
                case 0:
                    strCell = [NSString stringWithFormat:@"影院地址 : %@",_cinemainfo.address];
                    break;
                case 1:
                    strCell = [NSString stringWithFormat:@"公交路线 : %@", _cinemainfo.busline];
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
    return  strCell;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 3;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    NSInteger nRow = 0;
    switch (section) {
        case 0:
            nRow = 3;
            break;
        case 1:
            nRow = 2;
            break;
        case 2:
            nRow = 2;
            break;
        default:
            break;
    }
    return nRow;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{ 
    NSString * strCell = [self getStringWithIndex:indexPath];
    
    UIFont *cellFont = [UIFont systemFontOfSize:13];
    CGSize constraintSize = CGSizeMake(280.0f, MAXFLOAT);
    CGSize labelSize = [strCell sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
    
    return labelSize.height + 20;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";     
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];   
    
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
        cell.textLabel.lineBreakMode = UILineBreakModeWordWrap;
        cell.textLabel.numberOfLines = 0;
        cell.textLabel.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        [cell.textLabel setFont:[UIFont systemFontOfSize:13]];
    }    
 
    cell.textLabel.text = [self getStringWithIndex:indexPath];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;  
    
    return cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    //    TTURLAction *urlAction = [[[TTURLAction alloc] initWithURLPath:@"tt://moviedetail/MovieScheduleDetailsController"] autorelease];
    //    
    //    MovieInCinema *pCinema = [self.cinematable_array objectAtIndex:indexPath.row];
    //    urlAction.query = [NSDictionary dictionaryWithObject:pCinema forKey:@"moviedetail"];
    //    urlAction.animated = YES;
    //    [[TTNavigator navigator] openURLAction:urlAction];
}

////////////////////////////////////

@end
