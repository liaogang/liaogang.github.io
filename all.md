---
layout: layout_default  
title:  All
permalink: /all/
---

<div >
  <hr></hr>
  <ul >{% for post in site.posts %}{% if post.tag != 'private' and  post.tag != 'wallpaper' and  post.tag != 'tweet' %}
    <h1>
      <li> <span >{{ post.date | date: "%Y-%m-%d" }} </span> <a {% if post.tag == 'picture' %}href="{{ post.url | prepend: site.baseurl }}"{% endif %}>{{ post.title }}</a> </li> 
    </h1>{% if post.tag != 'picture' and post.tag != 'wallpaper' %}<div class="content">{{ post.content }}{% endif %}
    </div>
  <hr></hr>{% endif %}{% endfor %}
  </ul>
</div>