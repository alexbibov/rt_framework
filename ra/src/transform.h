#ifndef RA_TRANSFORM_H
#define RA_TRANSFORM_H

#include "optix.h"

#include "ra_fwd.h"
#include "contract_with_context.h"
#include "util/matrix_types.h"
#include "entity.h"
#include "util/log.h"

#include <memory>

namespace ra {

template<typename T> class RaTransformAttorney;

class RaTransform : public RaContractWithRaContext, public RaEntity
{
    friend class RaTransformAttorney<RaTransformable>;

public:
    RaTransform(RaContext const& optix_context);
    RaTransform(RaContext const& optix_context, util::mat4x4 const& transform);

    void setMatrix(util::mat4x4 const& transformation_matrix);
    util::mat4x4 getMatrix() const;

    /*! Combines this transform with provided transformation matrix.
     More precisely, if this transform is A and transform described by the transformation matrix is B, then
     after this operation this transform is given by A*B
    */
    RaTransform& operator*(util::mat4x4 const& transformation_matrix);

    // required by RaEntity interface
    bool isValid() const override;

private:
    std::shared_ptr<RTtransform_api> m_native_transform;
};

template<>
class RaTransformAttorney<RaTransformable>
{
    friend class RaTransformable;

    static RTtransform getNativeOptiXTransformHandle(RaTransform const& parent_transform)
    {
        return parent_transform.m_native_transform.get();
    }

    static void setTransformedObject(RaTransform const& parent_transform, RTobject transformed_object)
    {
        THROW_OPTIX_ERROR(parent_transform.nativeOptiXContextHandle(),
            rtTransformSetChild(parent_transform.m_native_transform.get(), transformed_object));
    }
};

}

#endif
