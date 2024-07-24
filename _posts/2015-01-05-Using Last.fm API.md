---

## layout: post\
title: Using [Last.fm](http://Last.fm) API\
date: 2015-01-05-09:27\
categories: tech

##MusicBrainz Identifier\
<https://musicbrainz.org/doc/MusicBrainz_Identifier>

One of MusicBrainz' aims is to be the universal lingua franca for music by providing a reliable and unambiguous form of music identification; this music identification is performed through the use of MusicBrainz Identifiers (MBIDs).

In a nutshell, an MBID is a 36 character Universally Unique Identifier that is permanently assigned to each entity in the database, i.e. artists, release groups, releases, recordings, works, labels, areas, places and URLs. MBIDs are also assigned to Tracks, though tracks do not share many other properties of entities. For example, the artist Queen has an artist MBID of 0383dadf-2a4e-4d10-a46a-e9e041da8eb3, and their song Bohemian Rhapsody has a recording MBID of ebf79ba5-085e-48d2-9eb8-2d992fbf0f6d.

An entity can have more than one MBID. When an entity is merged into another, its MBIDs redirect to the other entity.

##Scrobble\
To "scrobble" a song means that when you listen to it, the name of the song is sent to a Web site (for example, [Last.fm](http://Last.fm)) and added to your music profile.

可以理解为抓取一个或几个音乐播放记录到网页用户配置上。

##Now Playing Requests或Scrobble Requests的区别\
顾名思义Now Playing Requests显示用户当前正在播放的项目.\
而scrobble requests显示用户有效播放过的项目，所谓有效播放即:

1. 此音轨时间长度应该大于30秒。
2. 当前播放长度该大于总长度的一半，或大于4分种.

当这些条件达成时，一个scrobble request就生成了。但最方便的就是在音轨播放结束时提交这个scrobble记录。