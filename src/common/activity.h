#ifndef activity_h
#define activity_h

#include <Arduino.h>


class Activity {
    private:
        const byte MAX_NEXT_ACTIVITIES = 10;
        Activity* m_nextActivities[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
        byte m_addedActivities = 0;
    
    protected:
        byte m_nextActivityIndex = 0;

    public:
        Activity();

        void addNextActivity(Activity* anActivity);
        Activity* getNextActivity();

        virtual String className() = 0;
        virtual void start() = 0;
        virtual bool loop() = 0;
        virtual void action() = 0;

};

#endif
