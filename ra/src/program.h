#ifndef RA_PROGRAM_H
#define RA_PROGRAM_H

#include <string>
#include <map>

#include "vector_types.h"
#include "optix.h"

#include "ra_fwd.h"
#include "buffer.h"
#include "contract_with_context.h"
#include "entity.h"
#include "util/matrix_types.h"
#include "util/log.h"


namespace ra {

struct RaProgramId
{
    int native;
};

template<typename T>
class RaProgramAttorney;

//! Generic wrapper over OptiX program object
class RaProgram final : public RaContractWithRaContext, public RaEntity
{
    friend class RaProgramAttorney<RaContext>;
    friend class RaContractWithRaPrograms;

public:
    enum class Source { string, file };

private:
    RaProgram(RaContext const& optix_context,
        std::string const& source, Source source_type, std::string const& entry_point);
    
public:

    virtual ~RaProgram() = default;

    RaProgramId getId() const;

    void setVariableValue(std::string const& name, float value);
    void setVariableValue(std::string const& name, float2 const& value);
    void setVariableValue(std::string const& name, float3 const& value);
    void setVariableValue(std::string const& name, float4 const& value);

    void setVariableValue(std::string const& name, int value);
    void setVariableValue(std::string const& name, int2 const& value);
    void setVariableValue(std::string const& name, int3 const& value);
    void setVariableValue(std::string const& name, int4 const& value);

    void setVariableValue(std::string const& name, unsigned int value);
    void setVariableValue(std::string const& name, uint2 const& value);
    void setVariableValue(std::string const& name, uint3 const& value);
    void setVariableValue(std::string const& name, uint4 const& value);

    void setVariableValue(std::string const& name, util::mat2x2 const& value);
    void setVariableValue(std::string const& name, util::mat2x3 const& value);
    void setVariableValue(std::string const& name, util::mat2x4 const& value);

    void setVariableValue(std::string const& name, util::mat3x2 const& value);
    void setVariableValue(std::string const& name, util::mat3x3 const& value);
    void setVariableValue(std::string const& name, util::mat3x4 const& value);

    void setVariableValue(std::string const& name, util::mat4x2 const& value);
    void setVariableValue(std::string const& name, util::mat4x3 const& value);
    void setVariableValue(std::string const& name, util::mat4x4 const& value);

    void setVariableValue(std::string const& name, RaObjectHandle const& value);
    void setVariableValue(std::string const& name, RaProgramId const& program_id);

    void getVariableValue(std::string const& name, float& value);
    void getVariableValue(std::string const& name, float2& value);
    void getVariableValue(std::string const& name, float3& value);
    void getVariableValue(std::string const& name, float4& value);

    void getVariableValue(std::string const& name, int& value);
    void getVariableValue(std::string const& name, int2& value);
    void getVariableValue(std::string const& name, int3& value);
    void getVariableValue(std::string const& name, int4& value);

    void getVariableValue(std::string const& name, unsigned int& value);
    void getVariableValue(std::string const& name, uint2& value);
    void getVariableValue(std::string const& name, uint3& value);
    void getVariableValue(std::string const& name, uint4& value);

    void getVariableValue(std::string const& name, util::mat2x2& value);
    void getVariableValue(std::string const& name, util::mat2x3& value);
    void getVariableValue(std::string const& name, util::mat2x4& value);

    void getVariableValue(std::string const& name, util::mat3x2& value);
    void getVariableValue(std::string const& name, util::mat3x3& value);
    void getVariableValue(std::string const& name, util::mat3x4& value);

    void getVariableValue(std::string const& name, util::mat4x2& value);
    void getVariableValue(std::string const& name, util::mat4x3& value);
    void getVariableValue(std::string const& name, util::mat4x4& value);

    void getVariableValue(std::string const& name, RaObjectHandle& value);


    // required by RaEntity interface
    bool isValid() const override;

    void assignBuffer(std::string const& name, RaAbstractBuffer const& buffer);
    void assignProgram(std::string const& name, RaProgram const& program);

    bool checkVariableExistance(std::string const& name) const;

private:
    std::shared_ptr<RTprogram_api> m_native_optix_program;

    RTvariable fetch_variable(std::string const& name);
    RTvariable declare_variable_object(std::string const& name);
};


template<> class RaProgramAttorney<RaContext>
{
    friend class RaContext;

    static RaProgram createOptiXProgram(RaContext const& optix_context, std::string const& source, 
        RaProgram::Source source_type, std::string const& program_name)
    {
        return RaProgram{ optix_context, source, source_type, program_name };
    }
};


}

#endif
