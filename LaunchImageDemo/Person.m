//
//  Person.m
//  LaunchImageDemo
//
//  Created by 610582 on 2020/8/13.
//  Copyright © 2020 GFZ. All rights reserved.
//

#import "Person.h"

@implementation Person

- (instancetype)initWith:(NSString *)names withAge:(NSInteger)ages {
    if (self == [super init]) {
        self.name = names;
        self.ages = ages;
    }
    return self;
}

@end
