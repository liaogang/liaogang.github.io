---
layout: layout_default  
title:  All
permalink: /all/
---

<div >
  <ul >{% for post in site.posts %}{% if post.tag != 'private' and  post.tag != 'wallpaper' and  post.tag != 'tweet' %}
    <h1>
      <li> <span >{{ post.date | date: "%Y-%m-%d" }} </span> <a {% if post.tag == 'picture' %}href="{{ post.url | prepend: site.baseurl }}"{% endif %}>{{ post.title }}</a> </li> 
    </h1>
    {% if post.tag != 'picture' %}<div class="content">{{ post.content }}</div>{% endif %}
    {% endif %}{% endfor %}
  </ul>
</div>