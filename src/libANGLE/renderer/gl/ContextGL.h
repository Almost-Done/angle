//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ContextGL:
//   OpenGL-specific functionality associated with a GL Context.
//

#ifndef LIBANGLE_RENDERER_GL_CONTEXTGL_H_
#define LIBANGLE_RENDERER_GL_CONTEXTGL_H_

#include "libANGLE/renderer/ContextImpl.h"

namespace sh
{
struct BlockMemberInfo;
}

namespace rx
{
class FunctionsGL;
class RendererGL;
class StateManagerGL;
struct WorkaroundsGL;

class ContextGL : public ContextImpl
{
  public:
    ContextGL(const gl::ContextState &state, RendererGL *renderer);
    ~ContextGL() override;

    gl::Error initialize() override;

    // Shader creation
    CompilerImpl *createCompiler() override;
    ShaderImpl *createShader(const gl::ShaderState &data) override;
    ProgramImpl *createProgram(const gl::ProgramState &data) override;

    // Framebuffer creation
    FramebufferImpl *createFramebuffer(const gl::FramebufferState &data) override;

    // Texture creation
    TextureImpl *createTexture(const gl::TextureState &state) override;

    // Renderbuffer creation
    RenderbufferImpl *createRenderbuffer() override;

    // Buffer creation
    BufferImpl *createBuffer(const gl::BufferState &state) override;

    // Vertex Array creation
    VertexArrayImpl *createVertexArray(const gl::VertexArrayState &data) override;

    // Query and Fence creation
    QueryImpl *createQuery(GLenum type) override;
    FenceNVImpl *createFenceNV() override;
    SyncImpl *createSync() override;

    // Transform Feedback creation
    TransformFeedbackImpl *createTransformFeedback(
        const gl::TransformFeedbackState &state) override;

    // Sampler object creation
    SamplerImpl *createSampler(const gl::SamplerState &state) override;

    // Program Pipeline object creation
    ProgramPipelineImpl *createProgramPipeline(const gl::ProgramPipelineState &data) override;

    // Path object creation
    std::vector<PathImpl *> createPaths(GLsizei range) override;

    // Flush and finish.
    gl::Error flush() override;
    gl::Error finish() override;

    // Drawing methods.
    gl::Error drawArrays(const gl::Context *context,
                         GLenum mode,
                         GLint first,
                         GLsizei count) override;
    gl::Error drawArraysInstanced(const gl::Context *context,
                                  GLenum mode,
                                  GLint first,
                                  GLsizei count,
                                  GLsizei instanceCount) override;

    gl::Error drawElements(const gl::Context *context,
                           GLenum mode,
                           GLsizei count,
                           GLenum type,
                           const void *indices) override;
    gl::Error drawElementsInstanced(const gl::Context *context,
                                    GLenum mode,
                                    GLsizei count,
                                    GLenum type,
                                    const void *indices,
                                    GLsizei instances) override;
    gl::Error drawRangeElements(const gl::Context *context,
                                GLenum mode,
                                GLuint start,
                                GLuint end,
                                GLsizei count,
                                GLenum type,
                                const void *indices) override;
    gl::Error drawArraysIndirect(const gl::Context *context,
                                 GLenum mode,
                                 const void *indirect) override;
    gl::Error drawElementsIndirect(const gl::Context *context,
                                   GLenum mode,
                                   GLenum type,
                                   const void *indirect) override;

    // CHROMIUM_path_rendering implementation
    void stencilFillPath(const gl::Path *path, GLenum fillMode, GLuint mask) override;
    void stencilStrokePath(const gl::Path *path, GLint reference, GLuint mask) override;
    void coverFillPath(const gl::Path *path, GLenum coverMode) override;
    void coverStrokePath(const gl::Path *path, GLenum coverMode) override;
    void stencilThenCoverFillPath(const gl::Path *path,
                                  GLenum fillMode,
                                  GLuint mask,
                                  GLenum coverMode) override;
    void stencilThenCoverStrokePath(const gl::Path *path,
                                    GLint reference,
                                    GLuint mask,
                                    GLenum coverMode) override;
    void coverFillPathInstanced(const std::vector<gl::Path *> &paths,
                                GLenum coverMode,
                                GLenum transformType,
                                const GLfloat *transformValues) override;
    void coverStrokePathInstanced(const std::vector<gl::Path *> &paths,
                                  GLenum coverMode,
                                  GLenum transformType,
                                  const GLfloat *transformValues) override;
    void stencilFillPathInstanced(const std::vector<gl::Path *> &paths,
                                  GLenum fillMode,
                                  GLuint mask,
                                  GLenum transformType,
                                  const GLfloat *transformValues) override;
    void stencilStrokePathInstanced(const std::vector<gl::Path *> &paths,
                                    GLint reference,
                                    GLuint mask,
                                    GLenum transformType,
                                    const GLfloat *transformValues) override;
    void stencilThenCoverFillPathInstanced(const std::vector<gl::Path *> &paths,
                                           GLenum coverMode,
                                           GLenum fillMode,
                                           GLuint mask,
                                           GLenum transformType,
                                           const GLfloat *transformValues) override;
    void stencilThenCoverStrokePathInstanced(const std::vector<gl::Path *> &paths,
                                             GLenum coverMode,
                                             GLint reference,
                                             GLuint mask,
                                             GLenum transformType,
                                             const GLfloat *transformValues) override;

    // Device loss
    GLenum getResetStatus() override;

    // Vendor and description strings.
    std::string getVendorString() const override;
    std::string getRendererDescription() const override;

    // Debug markers.
    void insertEventMarker(GLsizei length, const char *marker) override;
    void pushGroupMarker(GLsizei length, const char *marker) override;
    void popGroupMarker() override;

    // State sync with dirty bits.
    void syncState(const gl::Context *context, const gl::State::DirtyBits &dirtyBits) override;

    // Disjoint timer queries
    GLint getGPUDisjoint() override;
    GLint64 getTimestamp() override;

    // Context switching
    void onMakeCurrent(const gl::Context *context) override;

    // Caps queries
    const gl::Caps &getNativeCaps() const override;
    const gl::TextureCapsMap &getNativeTextureCaps() const override;
    const gl::Extensions &getNativeExtensions() const override;
    const gl::Limitations &getNativeLimitations() const override;

    void applyNativeWorkarounds(gl::Workarounds *workarounds) const override;

    // Handle helpers
    const FunctionsGL *getFunctions() const;
    StateManagerGL *getStateManager();
    const WorkaroundsGL &getWorkaroundsGL() const;

    gl::Error dispatchCompute(const gl::Context *context,
                              GLuint numGroupsX,
                              GLuint numGroupsY,
                              GLuint numGroupsZ) override;

  private:
    RendererGL *mRenderer;
};

}  // namespace rx

#endif  // LIBANGLE_RENDERER_GL_CONTEXTGL_H_
