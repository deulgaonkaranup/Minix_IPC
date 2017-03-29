#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mutex>
#include "errorMsg.h"
#include "linkedList.h"

#define MAX_TOPICS 5
#define MAX_MESSAGES_PER_TOPIC 5
#define MAX_SUBSCRIBERS_PER_TOPIC 5
#define MAX_PUBLISHERS_PER_TOPIC 5
#define MAX_TOPIC_LENGTH 1024
#define MAX_MESSAGE_LENGTH 5000

using namespace std;

extern int errCode;

struct _sys_topic{
	char name[MAX_TOPIC_LENGTH];
	int owner_id;
};

struct _sys_topic_list{
	int index;
	_sys_topic *topics;
};

struct _sys_msg_usr{
	int proc_id;
};

struct _sys_subscribers{	
	int topic_index;
	int *users;
	int index;
};

struct _sys_subscribers_list{
	_sys_subscribers *sList;
	int index;
};

struct _sys_publishers{
	int topic_index;
	int *users;
	int index;
};

struct _sys_publishers_list{
	_sys_publishers *pList;
	int index;
};

struct _sys_message_internal{
	char message[MAX_MESSAGE_LENGTH];
	int *subscb_users;
	int count;
};

struct _sys_message{
	int topic_index;
	linkedList<_sys_message_internal> *messages;
};

struct _sys_message_list{
	_sys_message *mList;
	int index;
};

/* private */
void __initialize__();
int isValidTopic(string name);
bool isRegisteredPub(int id,int tIndex,int &topic_index);
bool isRegisteredSubs(int id,int tIndex,int &topic_index);
void copyArray(int *&dest,int *source, int length);
void getSubscriberIDs(int tindex,int *&subs_ids,int &count);
int getTopicIndexMessageList(int index);
bool __getMessage__(int index,int id,string &rmessage);

/* public */
int _topicLookup_(string name);
void _createTopic_(int id,string tName);
void _topicSubscriber_(int id,string name);
void _publishMessage_(int topic_index,int id,string message);
void _getMessage_(int topic_index,int id,string &message);
void _topicPublisher_(int id,string name);



