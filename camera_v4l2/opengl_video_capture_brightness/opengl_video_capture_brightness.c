#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <sys/mman.h>
#include <GL/glut.h>

int fd;
struct v4l2_format fmt;
struct v4l2_buffer buf;
void *buffer;

unsigned char* frame_data;

void init_v4l2(){
    // Open the video device
    fd = open("/dev/video0", O_RDWR);
    if(fd==-1)
    {
        perror("Opening video device");
        exit(EXIT_FAILURE);
    }

    // Set video format
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;
    if( ioctl(fd, VIDIOC_S_FMT, &fmt) == -1){
        perror("Setting pixel format");
        exit(EXIT_FAILURE);
    }

    // Request buffer
    struct v4l2_requestbuffers req;
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if(ioctl(fd, VIDIOC_REQBUFS, &req) == -1){
        perror("Requesting buffer");
        exit(EXIT_FAILURE);
    }

    // Query buffer
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;

    if(ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1){
        perror("Querying buffer");
        exit(EXIT_FAILURE);
    }

    buffer = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
    if(buffer == MAP_FAILED){
        perror("Mapping buffer");
        exit(EXIT_FAILURE);
    }

    // Queue buffer
    if(ioctl(fd, VIDIOC_QBUF, &buf) == -1){
        perror("Queueing buffer");
        exit(EXIT_FAILURE);
    }

    // Start streaming
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(fd, VIDIOC_STREAMON, &type) == -1){
        perror("Starting streaming");
        exit(EXIT_FAILURE);
    }
}

void set_brightness(int value) {
    struct v4l2_control control;
    control.id = V4L2_CID_BRIGHTNESS;
    control.value = value;
    if (ioctl(fd, VIDIOC_S_CTRL, &control) == -1) {
        perror("Setting brightness");
    }
}

void capture_frame(){
    // Dequeue buffer
    if( ioctl(fd, VIDIOC_DQBUF, &buf) == -1){
        perror("Dequeuing buffer");
        exit(EXIT_FAILURE);
    }

    // Copy buffer data to frame_data
    memcpy(frame_data, buffer, buf.bytesused);

    // Queue buffer
    if(ioctl(fd, VIDIOC_QBUF, &buf) == -1){
        perror("Queueing buffer");
        exit(EXIT_FAILURE);
    }

}

void display(){
    capture_frame();

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(640, 480, GL_RGB, GL_UNSIGNED_BYTE, frame_data);
    glutSwapBuffers();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'b' || key == 'B') {
        // Set brightness to 70
        set_brightness(70);
        printf("Brightness set to maximum.\n");
    }
}

void init_glut(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Camera Stream");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);  // Register keyboard handler
}

int main(int argc, char **argv)
{
    frame_data = (unsigned char*) malloc(640*480*3); // Allocate memory for a single frame

    init_v4l2();
    init_glut(argc, argv);
    glutMainLoop();

    // Clean up
    munmap(buffer, buf.length);
    close(fd);
    free(frame_data);

    printf("end of program\n");

    return 0;
}

