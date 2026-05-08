A video file is consisted of a *container* and *codec*
It's impossible to compare two video files based on their file extension alone

Codec stands for encoder-decoder. It is the algorithm used to transform videos into bit streams. It also compresses videos. Without codecs, even short video sizes would go up to terabytes.  
bit-rate or data rate is a property of the codec. It is the maximum number of bits the algorithm is allowed to write for each second of the video.
It is directly tied to the size of the outcome file.
Higher bit-rate means more data and better video quality because the algorithm can afford to include more details.
Lower bit-rate means lower quality because the algorithm has to sacrifice details in order to not pass the maximum number of bits allowed.

There are two different types of video compression:
- Intera-frame: compresses each frame individually. Higher quality and easier for editing.
	- M-JPEG (motion- jpeg) stores each frame as a still jpeg image
	- ProRes is a family of codecs by Apple
	- DNxHD is a family of codecs by Avid (a technology company which I've never even heard of tbh). DNxHR is another family that supports higher resolution (4K) videos.
- Inter-frame: stores only the different pixels from one frame to the next; harder to edit because we have to reconstruct the frames, like traveling in a linked list.
	- H.264 (AVC - advanced video coding) is defined in MPEG-4 and is the standard way videos are encoded on the internet. It is one of the most popular codecs used today.
	- H.265 - more recent version of H.264. Same quality but half the data rate and file size but requires more processing power and is not as easy to edit.
	- 

MPEG is a committee under ISO (International organization for standardization) that sets the standard for how compressed video and audio is represented as bits. More specifically, it sets the standard for how ...


A **container** simply organizes the data. It's job is to play the video and audio packets at the right time, sort of like an organizer. 
**Remuxing** is the process of changing a video file's container format without touching the underlying data.



```embed
title: "Color Spaces: Explained from the Ground Up -  Video Tech Explained"
image: "https://i.ytimg.com/vi/99v96TL-tuY/maxresdefault.jpg"
description: "At long last, here it is! A comprehensive, from-the-ground-up introduction to the foundational concepts used in modern color spaces. == Navigation ==00:00 In..."
url: "https://youtu.be/99v96TL-tuY"
favicon: ""
aspectRatio: "56.25"
```
Poor explanation because it jumps to the transformation matrix without explaining hue and saturation first