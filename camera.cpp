#include "camera.h"
#include <iostream>

Camera::Camera()
{
    // Initialize COM and MF
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    MFStartup(MF_VERSION);
    this->cam = NULL;
    this->rgbBuffer = NULL;
}

Camera::~Camera()
{
    // Shutdown COM and MF
    MFShutdown();
    CoUninitialize();
}

int Camera::getDevices(){
    HRESULT        hr;
    UINT32         count;
    IMFActivate    **devices   = NULL;
    IMFAttributes  *attributes = NULL;

    // Create the attribute TYPE
    hr = MFCreateAttributes(&attributes, 1);
    if(FAILED(hr)) { std::cerr << "Error: Cannot create attribute" << std::endl; exit(HRESULT_CODE(hr)); }

    hr = attributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
    if(FAILED(hr)) { std::cerr << "Error: Cannot set GUID" << std::endl; exit(HRESULT_CODE(hr)); }

    hr = MFEnumDeviceSources(attributes, &devices, &count);
    if(FAILED(hr)) { std::cerr << "Error: Cannot list devices" << std::endl; exit(HRESULT_CODE(hr)); }

    for(UINT32 i=0; i < count; i++)
        devices[i]->Release();
    attributes->Release();

    return count;
}

void Camera::setDevice(int id){
    HRESULT        hr;
    UINT32         count;
    IMFActivate    **devices   = NULL;
    IMFAttributes  *attributes = NULL;
    IMFMediaSource *mediaSource   = NULL;

    // Create the attribute TYPE
    hr = MFCreateAttributes(&attributes, 1);
    if(FAILED(hr)) { std::cerr << "Error: Cannot create attribute" << std::endl; exit(HRESULT_CODE(hr)); }

    hr = attributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
    if(FAILED(hr)) { std::cerr << "Error: Cannot set GUID" << std::endl; exit(HRESULT_CODE(hr)); }

    hr = MFEnumDeviceSources(attributes, &devices, &count);
    if(FAILED(hr)) { std::cerr << "Error: Cannot list devices" << std::endl; exit(HRESULT_CODE(hr)); }

    if (id >= 0 && id < count){
        hr = devices[0]->ActivateObject(IID_PPV_ARGS(&mediaSource));
        if(FAILED(hr)) { std::cerr << "Error: Cannot allocate Media Source" << std::endl; exit(HRESULT_CODE(hr)); }

        if(cam != NULL) cam->Release();
        hr = MFCreateSourceReaderFromMediaSource(mediaSource, NULL, &cam);
        if(FAILED(hr)) { std::cerr << "Error: Cannot allocate Source Reader" << std::endl; exit(HRESULT_CODE(hr)); }
        mediaSource->Release();
    }
    else{
        hr = MF_E_NOT_FOUND;
        if(FAILED(hr)) { std::cerr << "Error: Device not found" << std::endl; exit(HRESULT_CODE(hr)); }
    }

    for(UINT32 i=0; i < count; i++)
        devices[i]->Release();
    attributes->Release();
}

QImage Camera::getFrame(){
    if(cam != NULL){
        HRESULT hr = S_OK;
        DWORD streamIndex, flags;
        LONGLONG tmStamp;
        IMFSample *sample = NULL;

        while (sample == NULL){
            // ReadSample may return without a frame
            hr = cam->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, NULL, &streamIndex, &flags, &tmStamp, &sample);
            if(FAILED(hr)) { std::cerr << "Error: Sample not found" << std::endl; exit(HRESULT_CODE(hr)); }
        }

        IMFMediaBuffer *buffer;
        hr = sample->GetBufferByIndex(0, &buffer);
        if(FAILED(hr)) { std::cerr << "Error: Buffer not found" << std::endl; exit(HRESULT_CODE(hr)); }
        DWORD bSize;
        BYTE *frame;
        hr = buffer->Lock(&frame, NULL, &bSize);

        // Convert to RGB
        // From the test we assumed 2 byte per pixel,
        // a resolution of 640x480 and YUV422 byte layout.
        if(rgbBuffer != NULL)delete rgbBuffer;
        rgbBuffer = new BYTE[(bSize/2)*3];
        for(DWORD i = 0; i< bSize/2; i+=2){
            int y  = (frame[2*i]);
            int u  = (frame[2*i + 1]);
            int y2 = (frame[2*i + 2]);
            int v  = (frame[2*i + 3]);

            rgbBuffer[3*i + 0] = (int)getRedComponent  (y, u, v);
            rgbBuffer[3*i + 1] = (int)getGreenComponent(y, u, v);
            rgbBuffer[3*i + 2] = (int)getBlueComponent (y, u, v);

            rgbBuffer[3*i + 3] = (int)getRedComponent  (y2, u, v);
            rgbBuffer[3*i + 4] = (int)getGreenComponent(y2, u, v);
            rgbBuffer[3*i + 5] = (int)getBlueComponent (y2, u, v);
        }

        QImage img(rgbBuffer, 640, 480, QImage::Format_RGB888);
        buffer->Unlock();
        buffer->Release();
        sample->Release();
        //delete rgbFrame;
        return img;
    }
    return QImage();
}

// YUV 422 to RGB Conversion
float Camera::getRedComponent(float y, float u, float v){
    float px = 1.164*(y - 16) + 1.596*(v - 128);
    if(px < 0) return 0;
    if(px > 255) return 255;
    return px;
}
float Camera::getGreenComponent(float y, float u, float v){
    float px = 1.164*(y - 16) - 0.813*(v - 128) - 0.391*(u - 128);
    if(px < 0) return 0;
    if(px > 255) return 255;
    return px;
}
float Camera::getBlueComponent(float y, float u, float v){
    float px = 1.164*(y - 16) + 2.018*(u - 128);
    if(px < 0) return 0;
    if(px > 255) return 255;
    return px;
}
