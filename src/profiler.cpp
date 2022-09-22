#include <map>

#include <profiler/profiler.h>

static std::map<std::string, ProfileContext> contextMap;

Profiler::Profiler(const std::string& functionName, const std::string& context)
{
    this->context = context;
    this->functionName = functionName;

    ProfileContext& profileContext = this->getContext(this->context);

    ProfileNodeSharedPtr profileNode = profileContext.current;
    this->profileNode = this->getChildNode(profileNode, functionName);

    profileContext.current = this->profileNode;

    this->timer.startTimer();
}

Profiler::~Profiler()
{
    std::time_t elapsedTime = this->timer.getElapsedTime();

    this->profileNode->callCount++;
    this->profileNode->microseconds += elapsedTime;

    ProfileContext& profileContext = this->getContext(this->context);
    profileContext.current = this->profileNode->parent;

    if (profileContext.current == profileContext.root) {
        //Do something (like log?) with the profileContext.  It's finished.
    }
}

ProfileContext& Profiler::getContext(const std::string& context)
{
    if (contextMap.count(context) == 0) {
        ProfileContext profileContext;
        contextMap[context] = profileContext;
    }

    ProfileContext& profileContext = contextMap.at(context);
    return profileContext;
}

ProfileNodeSharedPtr Profiler::getChildNode(ProfileNodeSharedPtr profileNode, const std::string& functionName)
{
    if (profileNode->children.count(functionName) == 0) {
        ProfileNodeSharedPtr newProfileNode = std::make_unique<ProfileNode>();
        newProfileNode->parent = profileNode;

        profileNode->children[functionName] = newProfileNode;
    }

    return profileNode->children[functionName];
}
