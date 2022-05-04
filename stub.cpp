#include <BRENDER.H>
#define INITGUID
#include <Windows.h>
#include <AUDIOMAN.H>

// FIXME(clemenswasser): These are all empty implementations of the library functions from brender and audioman needed by 3dmovie, since we currently don't have the actual binaries.

// BRender Stub Functions:

/*
 * Setup
 */
void BR_PUBLIC_ENTRY BrBegin(void) {}
void BR_PUBLIC_ENTRY BrEnd(void) {}

/*
 * Callback function invoked when an actor is
 * rendered
 */
void BR_PUBLIC_ENTRY BrZbBegin(br_uint_8 colour_type, br_uint_8 depth_type) {}
void BR_PUBLIC_ENTRY BrZbEnd(void) {}
void BR_PUBLIC_ENTRY BrZbSceneRenderBegin(br_actor *world,
                                          br_actor *camera,
                                          br_pixelmap *colour_buffer,
                                          br_pixelmap *depth_buffer) {}
void BR_PUBLIC_ENTRY BrZbSceneRenderAdd(br_actor *tree) {}
void BR_PUBLIC_ENTRY BrZbSceneRenderEnd(void) {}

/*
 * Wrapper that inokes above therr calls in order
 */
void BR_PUBLIC_ENTRY BrZbSceneRender(
    br_actor *world,
    br_actor *camera,
    br_pixelmap *colour_buffer,
    br_pixelmap *depth_buffer) {}

/*
 * Picking
 */

int BR_PUBLIC_ENTRY BrScenePick2D(
    br_actor *world,
    br_actor *camera,
    br_pixelmap *viewport,
    int pick_x, int pick_y,
    br_pick2d_cbfn *callback, void *arg) { return 0; }
int BR_PUBLIC_ENTRY BrScenePick3D(
    br_actor *world,
    br_actor *actor,
    br_bounds *bounds,
    br_pick3d_cbfn *callback, void *arg) { return 0; }
int BR_PUBLIC_ENTRY BrModelPick2D(
    br_model *model,
    br_material *material,
    br_vector3 *ray_pos, br_vector3 *ray_dir,
    br_scalar t_near, br_scalar t_far,
    br_modelpick2d_cbfn *callback,
    void *arg) { return 0; }

/*
 * Misc. support  functions
 */
br_fixed_ls BR_ASM_CALL BrFixedSin(br_angle a) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedCos(br_angle a) { return 0; }
br_angle BR_ASM_CALL BrFixedASin(br_fixed_ls s) { return 0; }
br_angle BR_ASM_CALL BrFixedACos(br_fixed_ls c) { return 0; }
br_angle BR_ASM_CALL BrFixedATan2(br_fixed_ls x, br_fixed_ls y) { return 0; }
br_angle BR_ASM_CALL BrFixedATan2Fast(br_fixed_ls x, br_fixed_ls y) { return 0; }
br_fixed_ls BR_PUBLIC_ENTRY BrFixedSqrt(br_fixed_ls a) { return 0; }
br_fixed_ls BR_PUBLIC_ENTRY BrFixedPow(br_fixed_ls a, br_fixed_ls b) { return 0; }

/*
 * Euler Angles
 */
br_matrix34 *BR_PUBLIC_ENTRY BrEulerToMatrix34(br_matrix34 *mat, br_euler *euler) { return nullptr; }
br_euler *BR_PUBLIC_ENTRY BrMatrix34ToEuler(br_euler *euler, br_matrix34 *mat) { return nullptr; }
br_matrix4 *BR_PUBLIC_ENTRY BrEulerToMatrix4(br_matrix4 *mat, br_euler *src) { return nullptr; }
br_euler *BR_PUBLIC_ENTRY BrMatrix4ToEuler(br_euler *dest, br_matrix4 *mat) { return nullptr; }
br_quat *BR_PUBLIC_ENTRY BrEulerToQuat(br_quat *quat, br_euler *euler) { return nullptr; }
br_euler *BR_PUBLIC_ENTRY BrQuatToEuler(br_euler *euler, br_quat *quat) { return nullptr; }

/*
 * Actor Handling
 */
br_uint_32 BR_PUBLIC_ENTRY BrActorEnum(br_actor *parent, br_actor_enum_cbfn *callback, void *arg) { return 0; }
br_actor *BR_PUBLIC_ENTRY BrActorAdd(br_actor *parent, br_actor *a) { return nullptr; }
br_actor *BR_PUBLIC_ENTRY BrActorRemove(br_actor *a) { return nullptr; }
void BR_PUBLIC_ENTRY BrActorRelink(br_actor *parent, br_actor *actor) {}
br_uint_8 BR_PUBLIC_ENTRY BrActorToActorMatrix34(br_matrix34 *m, br_actor *a, br_actor *b) { return 0; }
void BR_PUBLIC_ENTRY BrActorToScreenMatrix4(br_matrix4 *m, br_actor *a, br_actor *camera) {}
br_actor *BR_PUBLIC_ENTRY BrActorAllocate(br_uint_8 actor_type, void *type_data) { return nullptr; }
void BR_PUBLIC_ENTRY BrActorFree(br_actor *a) {}
br_uint_32 BR_PUBLIC_ENTRY BrActorSearchMany(br_actor *root, char *pattern, br_actor **actors, int max) { return 0; }
br_actor *BR_PUBLIC_ENTRY BrActorSearch(br_actor *root, char *pattern) { return nullptr; }
br_bounds *BR_PUBLIC_ENTRY BrActorToBounds(br_bounds *b, br_actor *ap) { return nullptr; }
br_matrix34 *BR_PUBLIC_ENTRY BrBoundsToMatrix34(br_matrix34 *mat, br_bounds *bounds) { return nullptr; }

/*
 * Material Handling
 */
br_material *BR_PUBLIC_ENTRY BrMaterialAdd(br_material *material) { return nullptr; }
br_material *BR_PUBLIC_ENTRY BrMaterialRemove(br_material *material) { return nullptr; }
br_material *BR_PUBLIC_ENTRY BrMaterialFind(char *pattern) { return nullptr; }
br_material_find_cbfn *BR_PUBLIC_ENTRY BrMaterialFindHook(br_material_find_cbfn *hook) { return nullptr; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialAddMany(br_material **items, int n) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialRemoveMany(br_material **items, int n) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialFindMany(char *pattern, br_material **items, int max) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialCount(char *pattern) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialEnum(char *pattern,
                                          br_material_enum_cbfn *callback, void *arg) { return 0; }
void BR_PUBLIC_ENTRY BrMaterialUpdate(br_material *material, br_uint_16 flags) {}
br_material *BR_PUBLIC_ENTRY BrMaterialAllocate(char *name) { return nullptr; }
void BR_PUBLIC_ENTRY BrMaterialFree(br_material *m) {}

/*
 * 3x4 Matrix ops.
 */
void BR_PUBLIC_ENTRY BrMatrix34Copy(br_matrix34 *A, br_matrix34 *b) {}
void BR_PUBLIC_ENTRY BrMatrix34Mul(br_matrix34 *A, br_matrix34 *B, br_matrix34 *C) {}
void BR_PUBLIC_ENTRY BrMatrix34Pre(br_matrix34 *mat, br_matrix34 *A) {}
void BR_PUBLIC_ENTRY BrMatrix34Post(br_matrix34 *mat, br_matrix34 *A) {}
void BR_PUBLIC_ENTRY BrMatrix34Identity(br_matrix34 *mat) {}
void BR_PUBLIC_ENTRY BrMatrix34RotateX(br_matrix34 *mat, br_angle rx) {}
void BR_PUBLIC_ENTRY BrMatrix34PreRotateX(br_matrix34 *mat, br_angle rx) {}
void BR_PUBLIC_ENTRY BrMatrix34PostRotateX(br_matrix34 *mat, br_angle rx) {}
void BR_PUBLIC_ENTRY BrMatrix34RotateY(br_matrix34 *mat, br_angle ry) {}
void BR_PUBLIC_ENTRY BrMatrix34PreRotateY(br_matrix34 *mat, br_angle ry) {}
void BR_PUBLIC_ENTRY BrMatrix34PostRotateY(br_matrix34 *mat, br_angle ry) {}
void BR_PUBLIC_ENTRY BrMatrix34RotateZ(br_matrix34 *mat, br_angle rz) {}
void BR_PUBLIC_ENTRY BrMatrix34PreRotateZ(br_matrix34 *mat, br_angle rz) {}
void BR_PUBLIC_ENTRY BrMatrix34PostRotateZ(br_matrix34 *mat, br_angle rz) {}
void BR_PUBLIC_ENTRY BrMatrix34Rotate(br_matrix34 *mat, br_angle r, br_vector3 *axis) {}
void BR_PUBLIC_ENTRY BrMatrix34PreRotate(br_matrix34 *mat, br_angle r, br_vector3 *axis) {}
void BR_PUBLIC_ENTRY BrMatrix34PostRotate(br_matrix34 *mat, br_angle r, br_vector3 *axis) {}
void BR_PUBLIC_ENTRY BrMatrix34Translate(br_matrix34 *mat, br_scalar x, br_scalar y, br_scalar z) {}
void BR_PUBLIC_ENTRY BrMatrix34PreTranslate(br_matrix34 *mat, br_scalar x, br_scalar y, br_scalar z) {}
void BR_PUBLIC_ENTRY BrMatrix34PostTranslate(br_matrix34 *mat, br_scalar x, br_scalar y, br_scalar z) {}
void BR_PUBLIC_ENTRY BrMatrix34Scale(br_matrix34 *mat, br_scalar sx, br_scalar sy, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34PreScale(br_matrix34 *mat, br_scalar sx, br_scalar sy, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34PostScale(br_matrix34 *mat, br_scalar sx, br_scalar sy, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34ShearX(br_matrix34 *mat, br_scalar sy, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34PreShearX(br_matrix34 *mat, br_scalar sy, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34PostShearX(br_matrix34 *mat, br_scalar sy, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34ShearY(br_matrix34 *mat, br_scalar sx, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34PreShearY(br_matrix34 *mat, br_scalar sx, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34PostShearY(br_matrix34 *mat, br_scalar sx, br_scalar sz) {}
void BR_PUBLIC_ENTRY BrMatrix34ShearZ(br_matrix34 *mat, br_scalar sx, br_scalar sy) {}
void BR_PUBLIC_ENTRY BrMatrix34PreShearZ(br_matrix34 *mat, br_scalar sx, br_scalar sy) {}
void BR_PUBLIC_ENTRY BrMatrix34PostShearZ(br_matrix34 *mat, br_scalar sx, br_scalar sy) {}
void BR_PUBLIC_ENTRY BrMatrix34ApplyV(br_vector3 *A, br_vector3 *B, br_matrix34 *C) {}
void BR_PUBLIC_ENTRY BrMatrix34ApplyP(br_vector3 *A, br_vector3 *B, br_matrix34 *C) {}
void BR_PUBLIC_ENTRY BrMatrix34Apply(br_vector3 *A, br_vector4 *B, br_matrix34 *C) {}
void BR_PUBLIC_ENTRY BrMatrix34TApplyV(br_vector3 *A, br_vector3 *B, br_matrix34 *C) {}
void BR_PUBLIC_ENTRY BrMatrix34TApplyP(br_vector3 *A, br_vector3 *B, br_matrix34 *C) {}
void BR_PUBLIC_ENTRY BrMatrix34TApply(br_vector4 *A, br_vector4 *B, br_matrix34 *C) {}
br_scalar BR_PUBLIC_ENTRY BrMatrix34Inverse(br_matrix34 *out, br_matrix34 *in) { return 0; }
void BR_PUBLIC_ENTRY BrMatrix34LPInverse(br_matrix34 *A, br_matrix34 *B) {}
void BR_PUBLIC_ENTRY BrMatrix34LPNormalise(br_matrix34 *A, br_matrix34 *B) {}
void BR_PUBLIC_ENTRY BrMatrix34RollingBall(br_matrix34 *mat, int dx, int dy, int radius) {}

/**
 ** Fixed Point
 **/
br_fixed_ls BR_ASM_CALL BrFixedAbs(br_fixed_ls a) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMul(br_fixed_ls a, br_fixed_ls b) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMac2(br_fixed_ls a, br_fixed_ls b,
                                    br_fixed_ls c, br_fixed_ls d) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMac3(br_fixed_ls a, br_fixed_ls b,
                                    br_fixed_ls c, br_fixed_ls d,
                                    br_fixed_ls e, br_fixed_ls f) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMac4(br_fixed_ls a, br_fixed_ls b,
                                    br_fixed_ls c, br_fixed_ls d,
                                    br_fixed_ls e, br_fixed_ls f,
                                    br_fixed_ls g, br_fixed_ls h) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedSqr(br_fixed_ls a) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedSqr2(br_fixed_ls a,
                                    br_fixed_ls b) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedSqr3(br_fixed_ls a,
                                    br_fixed_ls b,
                                    br_fixed_ls c) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedSqr4(br_fixed_ls a,
                                    br_fixed_ls b,
                                    br_fixed_ls c,
                                    br_fixed_ls d) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedLength2(br_fixed_ls a, br_fixed_ls b) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedLength3(br_fixed_ls a,
                                       br_fixed_ls b,
                                       br_fixed_ls c) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedLength4(br_fixed_ls a,
                                       br_fixed_ls b,
                                       br_fixed_ls c,
                                       br_fixed_ls d) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedRLength2(br_fixed_ls a, br_fixed_ls b) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedRLength3(br_fixed_ls a,
                                        br_fixed_ls b,
                                        br_fixed_ls c) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedRLength4(br_fixed_ls a,
                                        br_fixed_ls b,
                                        br_fixed_ls c,
                                        br_fixed_ls d) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedDiv(br_fixed_ls a, br_fixed_ls b) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedDivF(br_fixed_ls a, br_fixed_ls b) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedDivR(br_fixed_ls a, br_fixed_ls b) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMulDiv(br_fixed_ls a,
                                      br_fixed_ls b,
                                      br_fixed_ls c) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMac2Div(br_fixed_ls a, br_fixed_ls b,
                                       br_fixed_ls c, br_fixed_ls d,
                                       br_fixed_ls e) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMac3Div(br_fixed_ls a, br_fixed_ls b,
                                       br_fixed_ls c, br_fixed_ls d,
                                       br_fixed_ls e, br_fixed_ls f,
                                       br_fixed_ls g) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedMac4Div(br_fixed_ls a, br_fixed_ls b,
                                       br_fixed_ls c, br_fixed_ls d,
                                       br_fixed_ls e, br_fixed_ls f,
                                       br_fixed_ls g, br_fixed_ls h,
                                       br_fixed_ls i) { return 0; }
br_fixed_ls BR_ASM_CALL BrFixedRcp(br_fixed_ls a) { return 0; }

/*
 * Lights
 */
void BR_PUBLIC_ENTRY BrLightEnable(br_actor *l) {}
void BR_PUBLIC_ENTRY BrLightDisable(br_actor *l) {}

/*
 * Pixelmap management
 */
br_pixelmap *BR_PUBLIC_ENTRY BrPixelmapAllocate(br_uint_8 type, br_uint_16 w, br_uint_16 h, void *pixels, int flags) { return nullptr; }
br_pixelmap *BR_PUBLIC_ENTRY BrPixelmapAllocateSub(br_pixelmap *pm,
                                                   br_uint_16 x, br_uint_16 y,
                                                   br_uint_16 w, br_uint_16 h) { return nullptr; }
void BR_PUBLIC_ENTRY BrPixelmapFree(br_pixelmap *pm) {}
br_pixelmap *BR_PUBLIC_ENTRY BrPixelmapMatch(br_pixelmap *src, br_uint_8 match_type) { return nullptr; }
br_pixelmap *BR_PUBLIC_ENTRY BrPixelmapClone(br_pixelmap *src) { return nullptr; }
br_uint_16 BR_PUBLIC_ENTRY BrPixelmapPixelSize(br_pixelmap *pm) { return 0; }
br_uint_16 BR_PUBLIC_ENTRY BrPixelmapChannels(br_pixelmap *pm) { return 0; }

/*
 * File operations
 */
br_model *BR_PUBLIC_ENTRY BrModelLoad(char *filename) { return nullptr; }
br_uint_32 BR_PUBLIC_ENTRY BrModelSave(char *filename, br_model *model) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrModelLoadMany(char *filename, br_model **models, br_uint_16 num) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrModelSaveMany(char *filename, br_model **models, br_uint_16 num) { return 0; }
br_material *BR_PUBLIC_ENTRY BrMaterialLoad(char *filename) { return nullptr; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialSave(char *filename, br_material *material) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialLoadMany(char *filename, br_material **materials, br_uint_16 num) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrMaterialSaveMany(char *filename, br_material **materials, br_uint_16 num) { return 0; }
br_pixelmap *BR_PUBLIC_ENTRY BrPixelmapLoad(char *filename) { return nullptr; }
br_uint_32 BR_PUBLIC_ENTRY BrPixelmapSave(char *filename, br_pixelmap *pixelmap) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrPixelmapLoadMany(char *filename, br_pixelmap **pixelmaps, br_uint_16 num) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrPixelmapSaveMany(char *filename, br_pixelmap **pixelmaps, br_uint_16 num) { return 0; }
br_actor *BR_PUBLIC_ENTRY BrActorLoad(char *filename) { return nullptr; }
br_uint_32 BR_PUBLIC_ENTRY BrActorSave(char *filename, br_actor *actor) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrActorLoadMany(char *filename, br_actor **actors, br_uint_16 num) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrActorSaveMany(char *filename, br_actor **actors, br_uint_16 num) { return 0; }

/*
 * Model Handling
 */
br_model *BR_PUBLIC_ENTRY BrModelAdd(br_model *model) { return nullptr; }
br_model *BR_PUBLIC_ENTRY BrModelRemove(br_model *model) { return nullptr; }
br_model *BR_PUBLIC_ENTRY BrModelFind(char *pattern) { return nullptr; }
br_model_find_cbfn *BR_PUBLIC_ENTRY BrModelFindHook(br_model_find_cbfn *hook) { return nullptr; }
br_uint_32 BR_PUBLIC_ENTRY BrModelAddMany(br_model **items, int n) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrModelRemoveMany(br_model **items, int n) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrModelFindMany(char *pattern, br_model **items, int max) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrModelCount(char *pattern) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrModelEnum(char *pattern,
                                       br_model_enum_cbfn *callback, void *arg) { return 0; }
void BR_PUBLIC_ENTRY BrModelUpdate(br_model *model, br_uint_16 flags) {}
void BR_PUBLIC_ENTRY BrModelApplyMap(br_model *model, int map_type, br_matrix34 *xform) {}
br_matrix34 *BR_PUBLIC_ENTRY BrModelFitMap(br_model *model, int axis_0, int axis_1, br_matrix34 *transform) { return nullptr; }
br_model *BR_PUBLIC_ENTRY BrModelAllocate(char *name, int nvertices, int nfaces) { return nullptr; }
void BR_PUBLIC_ENTRY BrModelFree(br_model *m) {}

/*
 * Custom calback support
 */
br_uint_8 BR_PUBLIC_ENTRY BrOnScreenCheck(br_bounds *bounds) { return 0; }
br_uint_8 BR_PUBLIC_ENTRY BrOriginToScreenXY(br_vector2 *screen) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrOriginToScreenXYZO(br_vector3 *screen) { return 0; }
br_uint_8 BR_PUBLIC_ENTRY BrPointToScreenXY(br_vector2 *screen, br_vector3 *point) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrPointToScreenXYZO(br_vector3 *screen, br_vector3 *point) { return 0; }
void BR_PUBLIC_ENTRY BrPointToScreenXYMany(br_vector2 *screens, br_vector3 *points, br_uint_32 npoints) {}
void BR_PUBLIC_ENTRY BrPointToScreenXYZOMany(br_vector3 *screens, br_uint_32 *outcodes, br_vector3 *points, br_uint_32 npoints) {}
void BR_PUBLIC_ENTRY BrSceneModelLight(br_model *model, br_material *default_material, br_actor *root, br_actor *a) {}

/*
 * Resource allocation
 */
void *BR_PUBLIC_ENTRY BrResAllocate(void *vparent, br_size_t size, int res_class) { return nullptr; }
void BR_PUBLIC_ENTRY BrResFree(void *vres) {}
char *BR_PUBLIC_ENTRY BrResStrDup(void *vparent, char *str) { return nullptr; }
void *BR_PUBLIC_ENTRY BrResAdd(void *vparent, void *vres) { return nullptr; }
void *BR_PUBLIC_ENTRY BrResRemove(void *vres) { return nullptr; }
br_uint_8 BR_PUBLIC_ENTRY BrResClass(void *vres) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrResSize(void *vres) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrResSizeTotal(void *vres) { return 0; }
br_uint_32 BR_PUBLIC_ENTRY BrResChildEnum(void *vres, br_resenum_cbfn *callback, void *arg) { return 0; }

/*
 * Used within custom model callbacks to render other models
 */
void BR_PUBLIC_ENTRY BrZbModelRender(br_actor *actor,
                                     br_model *model,
                                     br_material *material,
                                     br_uint_8 style,
                                     int on_screen,
                                     int use_custom) {}
br_renderbounds_cbfn *BR_PUBLIC_ENTRY BrZbSetRenderBoundsCallback(br_renderbounds_cbfn *new_cbfn) { return nullptr; }

// AudioMan Stub Functions:

STDAPI AllocSoundFromStream(LPSOUND FAR *ppSound, LPSTREAM pStream, BOOL fSpooled, LPCACHECONFIG lpCacheConfig) { return 0; }
STDAPI AllocSoundFromFile(LPSOUND FAR *ppSound, char FAR *szFileName, DWORD dwOffset, BOOL fSpooled, LPCACHECONFIG lpCacheConfig) { return 0; }
STDAPI AllocSoundFromMemory(LPSOUND FAR *ppSound, LPBYTE lpFileData, DWORD dwSize) { return 0; }
STDAPI AllocSilentSound(LPSOUND FAR *ppSound, LPWAVEFORMATEX lpwfx, DWORD dwSamples) { return 0; }
STDAPI_(LPMIXER)
GetAudioManMixer(void) { return nullptr; }
STDAPI AllocClipFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, DWORD dwStartPos, DWORD dwEndPos) { return 0; }
STDAPI AllocCacheFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, LPCACHECONFIG lpCacheConfig) { return 0; }
STDAPI AllocTrimFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc) { return 0; }
STDAPI AllocStereoFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc) { return 0; }
STDAPI AllocBiasFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc) { return 0; }
STDAPI AllocLoopFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, DWORD dwLoops) { return 0; }
STDAPI AllocConvertFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, LPWAVEFORMATEX lpwfx) { return 0; }
STDAPI AllocGainFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, float flLeft, float flRight) { return 0; }
STDAPI AllocDelayFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, DWORD dwDelay, DWORD dwReflectLeft, DWORD dwReflectRight, DWORD dwDuration, DWORD dwFlags) { return 0; }
STDAPI AllocGateFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, float flDBGate) { return 0; }
STDAPI AllocDistortFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, float flDBThreshold) { return 0; }
STDAPI AllocMixFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrcA, LPSOUND pSoundSrcB) { return 0; }
STDAPI AllocAppendFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrcA, LPSOUND pSoundSrcB, BOOL fAlign) { return 0; }
STDAPI AllocFaderFilter(LPSOUND FAR *ppSound, LPSOUND pSoundSrc, DWORD dwFadeTime, DWORD dwPosition) { return 0; }
STDAPI AllocScheduleFilter(LPSOUND FAR *ppSound, LPSCHEDULERCONFIG pSchedulerConfig) { return 0; }
STDAPI AllocRandomizeFilter(LPSOUND FAR *ppSound, LPRANDOMIZECONFIG pRandomizeConfig) { return 0; }
STDAPI AllocWaveOut(LPWAVEOUT FAR *ppWaveOut, LPMIXER pMixer) { return 0; }
STDAPI_(DWORD)
TimeToSamples(LPSOUND pSound, DWORD dwTime) { return 0; }
STDAPI_(DWORD)
SamplesToTime(LPSOUND pSound, DWORD dwSamples) { return 0; }
STDAPI_(DWORD)
SizeToSamples(LPSOUND pSound, DWORD dwSize) { return 0; }
STDAPI_(DWORD)
SamplesToSize(LPSOUND pSound, DWORD dwSamples) { return 0; }
STDAPI SoundToStreamAsWave(LPSOUND pSound, LPSTREAM pStream, LPDWORD pcbFileSize) { return 0; }
STDAPI SoundToFileAsWave(LPSOUND pSound, char FAR *pAbsFilePath) { return 0; }
STDAPI_(int)
DetectLeaks(BOOL fDebugOut, BOOL fMessageBox) { return 0; }