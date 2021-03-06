#ifndef RA_RAY_GENERATOR_H
#define RA_RAY_GENERATOR_H

#include <cstdint>
#include "ra_fwd.h"
#include "contract_with_context.h"
#include "contract_with_programs.h"
#include "entity.h"
#include "miss_shader_assembly.h"
#include "util/optional.h"


namespace ra {

template<typename T>
class RaRayGeneratorAttorney;

class RaRayGenerator : public RaContractWithRaContext, public RaContractWithRaPrograms, public RaEntity
{
    friend class RaRayGeneratorAttorney<RaSceneSection>;

public:
    RaRayGenerator(RaProgram const& ray_generation_shader, 
        uint32_t num_rays_x, uint32_t num_rays_y = 1U, uint32_t num_rays_z = 1U, 
        uint32_t entry_point_index = 0U);

    RaRayGenerator(RaProgram const& ray_generation_shader, RaMissShaderAssembly const& miss_shader_assembly,
        uint32_t num_rays_x, uint32_t num_rays_y = 1U, uint32_t num_rays_z = 1U,
        uint32_t entry_point_index = 0U);


    RaProgram getRayGenerationShader() const;
    util::Optional<RaMissShaderAssembly> getMissShaderAssembly() const;

    void setMissShaderAssembly(RaMissShaderAssembly const& miss_shader_assembly) const;

    // required by RaEntity interface
    bool isValid() const override;

    uint3 getGeneratorDimensions() const;
    unsigned int numberOfRays() const;

    virtual RaAbstractBuffer const& outputBuffer() const = 0;

protected:
    void setGeneratorDimensions(uint32_t num_rays_x, uint32_t num_rays_y, uint32_t num_rays_z);

    virtual void update(RaObjectHandle top_scene_object) const;
    virtual void launch() const;

    void update_topology(uint32_t new_num_rays_x, 
        uint32_t new_num_rays_y, 
        uint32_t new_num_rays_z, uint32_t new_entry_point_index = 0U) const;

private:
    std::shared_ptr<util::Optional<RaMissShaderAssembly>> m_p_miss_shader_assembly;

    mutable uint32_t m_num_rays_x;
    mutable uint32_t m_num_rays_y;
    mutable uint32_t m_num_rays_z;
    mutable uint32_t m_entry_point_index;
};

template<>
class RaRayGeneratorAttorney<RaSceneSection>
{
    friend class RaSceneSection;

    static void updateRayGenerator(RaRayGenerator const& parent_ray_generator, RaObjectHandle top_scene_object)
    {
        parent_ray_generator.update(top_scene_object);
    }

    static void launchRayGenerator(RaRayGenerator const& parent_ray_generator)
    {
        parent_ray_generator.launch();
    }
};

};

#endif
