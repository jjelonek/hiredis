//
//  redisconnector.h
//  redisconnector
//
//  Created by Jacek Jelonek on 28/10/14.
//  Copyright (c) 2014 recoded. All rights reserved.
//

#ifndef redisconnector_h
#define redisconnector_h

extern int openRedis(char *host, int port);
extern int closeRedis();
extern int execRedisCmd(char *cmd, char *replyStr, int *replyInt);

#endif
