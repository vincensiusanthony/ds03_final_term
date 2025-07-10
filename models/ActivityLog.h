#ifndef ACTIVITYLOG_H
#define ACTIVITYLOG_H

#include <string>
#include <ctime>

struct ActivityLog {
    std::string activity;
    std::time_t timestamp;

    ActivityLog() : activity(""), timestamp(std::time(nullptr)) {}
    ActivityLog(const std::string& activity)
        : activity(activity), timestamp(std::time(nullptr)) {}
};

#endif // ACTIVITYLOG_H