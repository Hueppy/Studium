#ifndef SEGMENTANZEIGE_H
#define SEGMENTANZEIGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Vorzeichnloser 8-Bit breiter Datentyp
 */
typedef uint8_t byte;

/**
 * @brief Aufzählungstyp für die Segmente
 */
typedef enum {
    SEG1 = 0,
    SEG2 = 1,
    SEG3 = 2,
    SEG4 = 3
} segment;

/**
 * @brief Aufzählungstyp für das Punkt-Segment
 */
typedef enum {
    OFF = 0,
    ON  = 1
} dot;

/**
 * @brief Aufzählungstyp für die Helligkeit
 */
typedef enum {
    DARK   = 0,
    MEDIUM = 1,
    BRIGHT = 7
} brightness;

#ifdef __cplusplus
}
#endif

#endif /* SEGMENTANZEIGE_H */
