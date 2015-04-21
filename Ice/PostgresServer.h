// PostgresServer.h
//
// Created by Mattt Thompson (http://mattt.me/)
// Copyright (c) 2012 Heroku (http://heroku.com/)
// 
// Portions Copyright (c) 1996-2012, The PostgreSQL Global Development Group
// Portions Copyright (c) 1994, The Regents of the University of California
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without a written agreement
// is hereby granted, provided that the above copyright notice and this
// paragraph and the following two paragraphs appear in all copies.
//
// IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
// DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
// LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//
// THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN
// "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATIONS TO
// PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

#import <Foundation/Foundation.h>

typedef enum {
	PostgresDataDirectoryIncompatible,
	PostgresDataDirectoryCompatible,
	PostgresDataDirectoryEmpty
} PostgresDataDirectoryStatus;

typedef enum : NSUInteger {
	PostgresServerUnreachable,
	PostgresServerRunning,
	PostgresServerWrongDataDirectory,
	PostgresServerStatusError
} PostgresServerStatus;

typedef void (^PostgresServerControlCompletionHandler)(BOOL success, NSError *error);

@interface PostgresServer : NSObject

@property (readonly) NSUInteger port;
@property (readonly) NSString *binPath;
@property (readonly) NSString *varPath;
@property (readonly) NSString *logfilePath;
@property (readonly) BOOL isRunning;

+ (NSString*)standardDatabaseDirectory;
+ (PostgresDataDirectoryStatus)statusOfDataDirectory:(NSString*)dir;
+ (NSString*)existingDatabaseDirectory;
+ (PostgresServer *)defaultServer;
+ (NSString*)dataDirectoryPreferenceKey;

- (id)initWithExecutablesDirectory:(NSString *)executablesDirectory
                 databaseDirectory:(NSString *)databaseDirectory;

- (void)startWithCompletionHandler:(PostgresServerControlCompletionHandler)completionBlock;
- (void)stopWithCompletionHandler:(PostgresServerControlCompletionHandler)completionBlock;

-(PostgresServerStatus)serverStatus;

@end