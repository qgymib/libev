#ifndef __EV_VERSION_H__
#define __EV_VERSION_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_VERSION Version
 * @{
 */

/**
 * @brief Major version.
 */
#define EV_VERSION_MAJOR            2

/**
 * @brief Minor version.
 */
#define EV_VERSION_MINOR            0

/**
 * @brief Patch version.
 */
#define EV_VERSION_PATCH            0

/**
 * @brief Version calculate helper macro.
 * @param[in] a     Major version.
 * @param[in] b     Minor version.
 * @param[in] c     Patch version.
 */
#define EV_VERSION(a, b, c)      (((a) << 24) + ((b) << 16) + (c))

/**
 * @brief Current version code.
 */
#define EV_VERSION_CODE             \
    EV_VERSION(EV_VERSION_MAJOR, EV_VERSION_MINOR, EV_VERSION_PATCH)

/**
 * @brief Get version code as c string.
 * @return      Version code.
 */
EV_API const char* ev_version_str(void);

/**
 * @brief Get version code as number.
 * @return      Version code
 */
EV_API unsigned ev_version_code(void);

/**
 * @} EV_VERSION
 */

#ifdef __cplusplus
}
#endif
#endif
