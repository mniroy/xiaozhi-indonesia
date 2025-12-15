# P3 Audio Format Conversion and Playback Tools

This directory contains scripts for processing P3 format audio files:

## 1. Audio Conversion Tool (convert_audio_to_p3.py)

Converts common audio files to P3 format (stream structure with 4-byte header + Opus packets) and performs loudness normalization.

### Usage

```bash
python convert_audio_to_p3.py <Input Audio File> <Output P3 File> [-l LUFS] [-d]
```

- Optional option `-l` specifies the target loudness for normalization, default is -16 LUFS.
- Optional option `-d` disables loudness normalization.

It is recommended to use `-d` to disable loudness normalization if the input audio meets any of the following conditions:
- The audio is too short
- The audio loudness has already been adjusted
- The audio comes from the default TTS (the default loudness of the TTS currently used by Xiaozhi is already -16 LUFS)

Example:
```bash
python convert_audio_to_p3.py input.mp3 output.p3
```

## 2. P3 Audio Playback Tool (play_p3.py)

Plays audio files in P3 format.

### Features

- Decodes and plays P3 format audio files
- Applies fade-out effect when playback ends or is interrupted by the user to avoid popping sounds
- Supports specifying the file to play via command-line arguments

### Usage

```bash
python play_p3.py <P3 File Path>
```

Example:
```bash
python play_p3.py output.p3
```

## 3. Audio Reversion Tool (convert_p3_to_audio.py)

Converts P3 format back to common audio files.

### Usage

```bash
python convert_p3_to_audio.py <Input P3 File> <Output Audio File>
```

The output audio file must have an extension.

Example:
```bash
python convert_p3_to_audio.py input.p3 output.wav
```

## 4. Audio/P3 Batch Conversion Tool

A GUI tool that supports batch conversion from Audio to P3, and P3 to Audio.

![](./img/img.png)

### Usage:
```bash
python batch_convert_gui.py
```

## Dependency Installation

Before using these scripts, please ensure the required Python libraries are installed:

```bash
pip install librosa opuslib numpy tqdm sounddevice pyloudnorm soundfile
```

Or use the provided requirements.txt file:

```bash
pip install -r requirements.txt
```

## P3 Format Description

The P3 format is a simple streaming audio format with the following structure:
- Each audio frame consists of a 4-byte header and an Opus encoded data packet
- Header format: [1 byte type, 1 byte reserved, 2 bytes length]
- Sampling rate fixed at 16000Hz, Mono
- Frame duration is 60ms