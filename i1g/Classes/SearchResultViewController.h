//
//  SearchResultViewController.h
//  i1G
//
//  Created by Nick Xiao on 2/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NXHttpClient.h"


@interface SearchResultViewController : UITableViewController<UISearchBarDelegate> {
	UISearchBar *searchBar;
	HttpConnectionId hidSearch;
}

@property (nonatomic, retain) IBOutlet UIViewController *searchContainer;
@end
