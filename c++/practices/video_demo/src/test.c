/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-10 08:10:53
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-10 09:40:02
 * @FilePath: /c++/practices/video_demo/src/test.c
 * @Description: 注释信息
 */
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <stdio.h>

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame)
{
    FILE *pFile;
    char szFilename[32];
    int y;

    // 打开文件
    sprintf(szFilename, "frame%d.ppm", iFrame);
    pFile = fopen(szFilename, "wb");
    if (pFile = NULL)
    {
        return;
    }

    // 写入header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    // 写入像素数据
    for (y = 0; y < height; y++)
    {
        fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width * 3, pFile);
    }

    // 关闭文件
    fclose(pFile);
}

int main(int argc, char *argv[])
{
    AVFormatContext *pFormatCtx = NULL;
    int i, videoStream;
    AVCodecContext *pCodecCtx = NULL;
    AVCodec *pCodec = NULL;
    AVFrame *pFreme = NULL;
    AVFrame *pFrameRGB = NULL;
    AVPacket packet;
    int frameFinished;
    int numBytes;
    uint8_t *buffer = NULL;

    AVDictionary *optionDict = NULL;
    struct SwsContext *sws_ctx = NULL;

    if (argc < 2)
    {
        printf("请输入一个视频文件\n");
        return -1;
    }

    // 注册所有的 formats 和codecs
    av_register_all();

    // 打开视频文件
    if (avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0)
    {
        printf("不能打开文件");
        return -1;
    }

    // 检索文件中的流信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        printf("检索不到流信息");
        return -1;
    }

    // 打印资源的信息
    av_dump_format(pFormatCtx, 0, argv[1], 1);

    // 找到第一个视频流
    videoStream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
            break;
        }
    }

    if (videoStream == -1)
    {
        printf("没有找到视频流");
        return -1;
    }

    // 获取一个指向视频流编解码器上下文的指针
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    // 给视频流找解码器
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL)
    {
        fprintf(stderr, "暂无适配的解码器！\n");
        return -1;
    }

    // 打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, &optionDict) < 0)
    {
        printf("解码器运行失败");
        return -1;
    }

    // allocate video frame
    pFreme = av_frame_alloc();

    // allocate an avframe structure
    pFrameRGB = av_frame_alloc();
    if (pFrameRGB == NULL)
    {
        return -1;
    }

    // 确定需要的缓冲区大小并分配缓冲区
    numBytes = avpicture_get_size(AV_PIX_FMT_RGB24,
                                  pCodecCtx->width,
                                  pCodecCtx->height);
    buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

    // 读取帧并保存前5帧到磁盘
    i = 0;
    while (av_read_frame(pFormatCtx, &packet))
    {
        // 判断是否是来自视频流的数据包
        if (packet.stream_index == videoStream)
        {
            // 解码视频帧
            avcodec_decode_video2(pCodecCtx, pFreme, &frameFinished,
                                  &packet);

            if (frameFinished)
            {
                //将图像从其原生格式转换为RGB格式
                sws_scale(
                    sws_ctx,
                    (uint8_t const *const *)pFreme->data,
                    pFreme->linesize,
                    0,
                    pCodecCtx->height,
                    pFrameRGB->data,
                    pFrameRGB->linesize);

                // 保存帧到磁盘
                SaveFrame(
                    pFrameRGB,
                    pCodecCtx->width,
                    pCodecCtx->height,
                    i);
                printf("decode %d frame\n", i);
                i++;
            }
        }

        // 释放av_read_frame分配的packet
        av_free_packet(&packet);
    }

    // 释放RGB图片
    av_free(buffer);
    av_free(pFrameRGB);

    // 释放YUV帧
    avcodec_close(pCodecCtx);

    // 关闭视频文件
    avformat_close_input(&pFormatCtx);

    return 0;
}