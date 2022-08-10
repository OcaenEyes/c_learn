<!--
 * @Author: OCEAN.GZY
 * @Date: 2022-08-10 05:25:14
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-10 08:06:33
 * @FilePath: /c++/practices/video_demo/readme.md
 * @Description: 注释信息
-->

```
sudo apt-get update
sudo apt-get -y install autoconf automake build-essential libass-dev libfreetype6-dev \
  libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libxcb1-dev libxcb-shm0-dev \
  libxcb-xfixes0-dev pkg-config texinfo zlib1g-dev
sudo apt-get install yasm
sudo apt-get install libx264-dev        # H.264 依赖库
sudo apt-get install cmake mercurial
sudo apt-get install libfdk-aac-dev        # aac audio 依赖库
sudo apt-get install libmp3lame-dev        # mp3 audio 依赖库
sudo apt-get install libopus-dev        # Opus audio 依赖库
sudo apt-get install ctags                # 文档工具
```

### ffmpeg命令行工具

fmpeg 工具是一个高效快速的命令行工具，进行视音频不同格式之间的转换，

ffmpeg可以读取任意数量的输入“文件”（可以是常规文件，管道，网络流，抓取设备等）读取，由 -i 选项指定，并写入任意数量的输出“文件” （由纯输出文件名指定，在命令行中发现的不能被解释为选项的任何东西被认为是输出文件名。）

每个输入或输出文件原则上可以包含任意数量的不同类型的流（视频/音频/字幕/附件/数据）。 流的数量或类型可以由容器格式规定。 选择哪些输入并输出到哪个要么自动完成，要么使用-map选项。

- 将输出文件的视频比特率设置为64 kbit/s
```
ffmpeg -i input.avi -b:v 64k -bufsize 64k output.avi
```

- 强制输出文件的帧速率24帧：
```
ffmpeg -i input.avi -r 24 output.avi
```

- 强制输入文件的帧速率(仅对raw格式有效)为1帧和输出文件的帧速率为24帧的：
```
ffmpeg -r 1 -i input.m2v -r 24 output.avi
```
ffmpeg 的转码流程可以由下图表示：


（ ffmpeg 调用 libavformat 库（包含 demuxers ）来读取输入文件，并从中获取包含编码数据的数据包。 当有多个输入文件时，ffmpeg 尝试通过输入流上的时间戳来保持它们的同步。

编码分组后传递到解码器。 解码器可以通过滤波进一步处理的未压缩帧（原始视频/ PCM音频/ ...）。 在过滤之后，帧被传递到编码器，编码它们并输出编码分组。 最后，它们被传递到复用器，复用器将编码的数据包写入输出文件。）


### ffserver
ffserver 是用于音频和视频的流服务器。 它支持多种推送方式，从文件流传输或者实时流推送。 如果有足够大的推送存储空间，还可以查找每个实时流的位置。

ffserver 从一些实例接收预录制文件或 FFM 流作为输入，然后通过 RTP / RTSP / HTTP 将其流式传输。

对于每个推送，可以有不同格式的不同输出流，每个格式由配置文件中的 部分指定。

推送发布的网址如：
```
http://ffserver_ip_address:http_port/feed_name
```
其中 ffserver_ip_address 是安装 ffserver 的计算机的 IP 地址，http_port 是 HTTP 服务器的端口号（通过 HTTPPort 选项配置），feed_name 是配置文件中定义的相应订阅源的名称。

多个流可以连接到同一个推送上。例如，可以使用以下图形描述的情况：

我们可以使用下面的命令来开启一个简单的范例：
```
ffserver -f doc/ffserver.conf &
ffmpeg -i INPUTFILE http://localhost:8090/feed1.ffm
```
然后可以在其他的电脑上输入 url 查看：
```
http://<linuxbox>:8090/test.asf
```


### ffplay

ffplay 是一个使用 ffmpeg 库和 sdl 库的非常简单和便携的媒体播放器。 它主要用作各种 ffmpeg api 的测试平台。

每个流使用一些选项，例如比特率或编解码器。 流指定符用于精确地指定选项所属的流。流指定符是一个字符串，通常添加选项名称，并用冒号分隔。 例如。 -codec：a：1 ac3 包含a：1 流标识符，它匹配第二个音频流。 因此，它将为第二个音频流选择 ac3 编解码器。流指定符可以匹配多个流，以便将选项应用于所有流。 例如。 -b：128k 中的流说明符匹配所有音频流。空流说明符匹配所有流。 例如，-codec copy 或 -codec：copy 将复制所有流，而不重新编码。流标识符的可能形式是：


> stream_index ： 使用此索引匹配流。 例如。 -threads：1 4 将第二个流的线程计数设置为4。

> stream_type[:stream_index]： stream_type 是以下之一：视频的'v'或'V'，音频的'a'，字幕的's'，数据的'd'和 附件的't'。 'v'匹配所有视频流，'V'仅匹配未附加图片。如果给出 stream_index，则它匹配此类型的流 stream_index。 否则，它匹配此类型的所有流。

> p:program_id[:stream_index]：如果给出 stream_index，则它将流与程序中具有 id program_id 的数字 stream_index 匹配。 否则，它匹配程序中的所有流。

> stream_id or i:stream_id ： 通过流 id 匹配流（例如 MPEG-TS 容器中的 PID ）。

> m:key[:value] ： 匹配具有指定值的元数据标记键的流。 如果未指定值，则将包含给定标记的流与任何值 进行匹配。匹配具有可用配置的流，必须定义编解码器，并且存在诸如视频尺寸或音频采 样率的基本信息。请注意，在ffmpeg中，通过元数据进行的匹配仅适用于输入文件。


### ffprobe

ffprobe从多媒体流收集信息，并以人和机器可读的方式打印。

例如，它可以用于检查由多媒体流使用的容器的格式以及包含在其中的每个媒体流的格式和类型。

如果在输入中指定了文件名，ffprobe 将尝试打开并探测文件内容。如果文件无法打开或识别为多媒体文件，则返回正的退出代码。

ffprobe 可以用作独立应用或与文本过滤器组合，其可以执行更复杂的处理，例如，统计处理或绘图。

选项用于列出 ffprobe 支持的某些格式，或用于指定要显示的信息，以及用于设置 ffprobe 将如何显示它。

ffprobe 输出设计为可以通过文本过滤器轻松解析，并且由选定 writer（由 print_format 选项指定）定义的一个或多个部分组成。

存储在容器或流中的元数据标签被识别并打印在相应的 “FORMAT” ，“STREAM” 或 “PROGRAM_STREAM” 部分中。


####  涉及到的开发库
##### libavutil
libavutil 库是一个实用程序库，以辅助多媒体编程。 它包含安全可移植字符串函数，随机数生成器，数据结构，附加数学函数，加密和多媒体相关功能。 它不是 libavcodec 和 libavformat 所需的代码的库。

这个库的目标是：

模块化        它应该具有很少的相互依赖性和在 ./configure 期间禁用单个部件的可能性。
小          源和对象都应该小。
高效         它应该具有低CPU和内存使用。
有用         它应该添加人们很需要的功能。

#####  libavcodec
libavcodec 库提供通用编码/解码框架，并包含用于音频，视频和字幕流的多个解码器和编码器，以及多个比特流滤波器。

共享架构提供从比特流 i/o 到 dsp 优化的各种服务，并且使得它适合于实现健壮和快速的编解码器。

#####  libavformat
libavformat 库为音频、视频和字幕流的复用和解复用（多路复用和解复用）提供了一个通用框架。 它包括多媒体容器格式的多个多路复用器和多路分解器。

它还支持几种输入和输出协议来访问媒体资源。

#####  libavdevice
libavdevice 库提供了一个通用框架，用于从许多常见的多媒体输入/输出设备抓取和渲染，并支持多个输入和输出设备，包括 Video4Linux2，VfW，DShow和ALSA。

#####  libavfilter
libavfilter 库提供了一个通用的音频/视频过滤框架，包含几个过滤器，源和接收器模块。

#####  libswscale
libswscale 库执行高度优化的图像缩放和颜色空间和像素格式转换操作。

具体来说，此库执行以下转换：

重新调整：是更改视频大小的过程。 有几个重新调整选项和算法可用。 这通常是有损耗的过程。

像素格式转换：是转换图像的图像格式和颜色空间的过程，例如从平面 YUV420P 到 RGB24 转换。 它还可以处理 packed 转换，即从 packed 布局（属于在同一缓冲器中交织的不同平面的所有像素）转换为平面布局（属于存储在专用缓冲器或“平面”中的相同平面的所有样本）的转换。

如果源和目标颜色空间不同，这通常是有损过程。

##### libswresample
libswresample 库执行高度优化的音频重采样，重新矩阵化和样本格式转换操作。

具体来说，此库执行以下转换：

重新采样：是改变音频速率的过程，例如从 44100Hz 的高采样率到 8000Hz 。从高到低采样率的音频转换是有损耗的过程。有几个重采样选项和算法可用。

格式转换：是将采样类型（例如从16位有符号采样转换为无符号8位或浮点采样）的过程。当从 packed 布局（所有属于在相同缓冲器中交错的不同通道的样本）到平面布局（属于存储在专用缓冲器或“平面”中的相同通道的所有样本）时，它还处理 packed 转换。

重新矩阵化：是改变通道布局的过程，例如从立体声到单声道。当输入通道不能映射到输出流时，该过程是有损的，因为它涉及不同的增益因子和混合。
通过专用选项启用各种其他音频转换（例如拉伸和填充）。


### 制作动画屏幕捕捉

电影文件有几个部分组成，文件本身称为容器，容器的类型决定文件中信息的位置。 本节实验容器的示例是 avi 和quicktime。 接下来，我们需要处理很多流：例如通常有一个音频流和一个视频流。流中的数据元素被称为帧。 每个流由不同种类的编解码器编码。 编解码器定义实际数据如何被 COTED和 DECDODE --- 因此名称 CODEC。 编解码器的示例是 DivX 和 MP3 。 然后从流中读取分组。 数据包是可以包含数据位的数据片段，这些数据被解码成我们最终可以为我们的应用程序处理的原始帧。 为了我们的目的，每个分组包含完整的帧，或者在音频的情况下多个帧。

处理视频和音频流是非常容易的，属于基本层次：
```
从文件中找到视频流
从视频流中读取数据包
如果不是一帧完整的数据就继续执行上一步
对帧数据做一些处理
然后循环执行以上操作，直到结束
```
在本实验中我们将对帧数据做一些处理，比如将每一帧的图像转为 jpg或者bmp或者ppm等格式保存下来。

