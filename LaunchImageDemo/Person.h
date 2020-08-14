//
//  Person.h
//  LaunchImageDemo
//
//  Created by 610582 on 2020/8/13.
//  Copyright © 2020 GFZ. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Person : NSObject
@property(nonatomic,strong) NSString *name;
@property(nonatomic,assign) NSInteger  ages;
-(instancetype)initWith:(NSString *)names withAge:(NSInteger)ages;

@end

NS_ASSUME_NONNULL_END
