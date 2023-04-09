#include <common/activity.h>

//////////////////// Constructor
Activity::Activity() {}

//////////////////// Public methods implementation
void Activity::addNextActivity(Activity* anActivity) {
    if (m_addedActivities >= MAX_NEXT_ACTIVITIES)
        return;

    m_addedActivities++;
    m_nextActivities[m_addedActivities - 1] = anActivity;
}

Activity* Activity::getNextActivity() {
    if (m_addedActivities <= m_nextActivityIndex)
        return NULL;
    
    Activity* next = m_nextActivities[m_nextActivityIndex];
    return next;
}

//////////////////// Private methods implementation
