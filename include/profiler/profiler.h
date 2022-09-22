#pragma once

#include <map>
#include <memory>
#include <stack>
#include <string>

#include <cstdint>

#include <profiler/timer.h>

struct ProfileNode
{
    using ProfileNodeSharedPtr = std::shared_ptr<ProfileNode>;

    std::map<std::string, ProfileNodeSharedPtr> children;
    ProfileNodeSharedPtr parent = nullptr;

    std::time_t microseconds = 0;
    std::uint32_t callCount = 0;
};

using ProfileNodeSharedPtr = std::shared_ptr<ProfileNode>;

struct ProfileContext
{
    ProfileNodeSharedPtr root;
    ProfileNodeSharedPtr current;

    ProfileContext()
    {
        this->root = std::make_unique<ProfileNode>();
        this->current = this->root;
    }
};

class Profiler
{
protected:
    MicrosecondTimer timer;

    std::string context;
    std::string functionName;

    ProfileNodeSharedPtr profileNode;

    ProfileContext& getContext(const std::string& context);
    ProfileNodeSharedPtr getChildNode(ProfileNodeSharedPtr profileNode, const std::string& functionName);
public:
    Profiler(const std::string& functionName, const std::string& context = "default");
    ~Profiler();
};
