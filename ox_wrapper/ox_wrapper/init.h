#ifndef OX_WRAPPER_INIT_H
#define OX_WRAPPER_INIT_H

#include "fwd.h"
#include "util/log.h"

#include <memory>
#include <fstream>

namespace ox_wrapper
{

class OxInit final
{
public:
    OxInit(
        std::string const& global_path_prefix,
        std::string const& path_to_settings);

    ~OxInit();
    
    OxContext const& context() const;
    util::Log const& logger() const;
    std::string loggerPath() const;

private:
    std::unique_ptr<OxContext> m_context;
    std::string m_path_to_settings_json;
    std::string m_logging_path;

    std::ofstream m_logging_stream;
};

}

#endif