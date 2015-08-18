---
layout: post
title:  About DLNA  
date:   2015-05-25
categories: tech
---

##1.1 Architectures and Protocols体系结构和协议  

The Interoperability Guidelines consists of ten parts covering Architecture and Protocols, Media Formats, Link Protection, DRM Interoperability Systems, Device Profiles, HTML RUI, Authentication, Diagnostics, HTTP Adaptive Delivery, and Low Power Mode.    

这个操作指南包含十部分: 体系结构和协议，媒体格式，链接保护，DRM互操作系统，设备描述，HTML RUI,身份认证，诊断，HTTP自适应交付和低功率模式。  

It provides vendors with the information needed to build interoperable networked platforms and devices for the digital home.   
 
它提供了vendors with the information needed to build可互操作的网络化Platforms and devices for the数字家庭。  

 The necessary standards and technologies are available now to enable products to be built for networked entertainment centric usages.    
  
  
## upnp av ContentDirectory v1 Service
###2.8.9 Playlist Manipulation 播放列表控制
####2.8.9.1  Playlist file representation in CDS 

A playlist file is represented as an object of the playlist class (object.item.playlist).   

The format of the playlist is indicated by the MIME type section of the res@protocolInfo property on the playlist object.  

If a search were performed for all objects of class object.item.playlist in the content directory, it would return a result of the following form:

## Searching 搜索动作

The Search() action is designed to allow a control point to search for objects in the content directory that match a given search criteria (see section 2.5.5).  
Search() 动作被设计用于允许一个control point来搜索要求的匹配对象


In addition, the Search() action supports the following features:  

* Incremental result retrieval i.e. in the context of a particular request the control point can restrict the number (and the starting offset) of objects returned in the result.  
  增量结果检索 , 例如，设置相应搜索条件，control point能限制搜索返回结果的对象的数量（和开始下标）。  
  
* Sorting. The result can be requested in a particular sort order. The available sort orders are expressed in the return value of the GetSortCapabilities action.
排序. 

* Filtering. The result data can be filtered to only include a subset of the properties available on the object (see section 2.5.7). Note that certain properties may not be filtered out in order to maintain the validity of the result data fragment. If a non-filterable property is left out of the filter set, it will still be included in the result.
过滤。