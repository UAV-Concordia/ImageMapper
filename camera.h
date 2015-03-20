#ifndef CAMERA_H
#define CAMERA_H

#include <QList>
#include <QImage>
#include <mfapi.h>
#include <Mfobjects.h>
#include <mfidl.h>
#include <Mferror.h>
#include <mfreadwrite.h>

/**
 * This class allows to query the image capture device
 * using Media Foundation (Windows 7 +).
 * An instance of this class map to a single device at the time.
 */
class Camera
{
public:
    Camera();
    ~Camera();

    /**
     * Associate a capturing device.
     * There could be more than one capture device,
     * then this method associate a video device to
     * this instance.
     *
     * The device id can be queried with getDevices()
     *
     * @see #getDevices();
     * @param id device index;
     */
    void setDevice(int id);

    /**
     * Retrieve the total number of video devices.
     * Devices' ids are within 0 and getDevices.
     *
     * @return number of video devices
     */
    int getDevices();

    /**
     * Get the next available frame.
     * @return captured frame
     */
    QImage getFrame();

private:
    BYTE            *rgbBuffer;
    IMFSourceReader *cam;
    float getRedComponent(const float y, const float u, const float v);
    float getGreenComponent(const float y, const float u, const float v);
    float getBlueComponent(const float y, const float u, const float v);
};

#endif // CAMERA_H
