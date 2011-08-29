#ifndef TESTMYSELF_H_INCLUDED
#define TESTMYSELF_H_INCLUDED

#include <iostream>
using namespace std;

#include "CompManager.h"
#include "GroupManager.h"
#include "Connector.h"
#include "Force.h"
#include "KPair.h"
#include "Segment.h"
#include "Group.h"
#include "Group1.h"
#include "Group2.h"
#include "GroupS.h"
#include "GroupT.h"
#include "GroupSTS.h"
#include "GroupTSS.h"
#include "GroupTST.h"
#include "GroupTTS.h"
#include "GroupTTT.h"

void PrintConnectorInfo(Connector *c, bool extended = true, int level = 0);
void PrintSegmentInfo(Segment *s, bool extended = true, int level = 0);
void PrintKPInfo(KPair *K, bool extended = true, int level = 0);
void PrintForceInfo(Force *f, bool extended = true, int level = 0);
void PrintGroupInfo(Group *g, bool extended = true, int level = 0);

class CompManager;
class GroupManager;

void PrintCompManagerInfo(CompManager *cm, int level = 0);
void PrintGroupsInfo(GroupManager &gm);

#endif // TESTMYSELF_H_INCLUDED
