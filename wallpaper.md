---
layout: layout_default  
permalink: /wallpaper/
tag: wallpaperMaker
---

<div >
  <hr></hr>

<h1> wallpaper index: {{  site.wallpaperIndex }}</h1>


{{ var prevIndex = site.wallpaperIndex }}

{% for post in site.posts limit post.tag == 'wallpaper' %}
  {% if i == prevIndex  %}   


{% if post.previous != nil %}
<a href="{{ post.previous.url }}">Prev</a>
{% endif %}

{% if post.next != nil %}
  <a href="{{ post.next.url }}">Next</a>  
{% endif %}


  <div class="content">{{ post.title }} </div>
  <hr></hr>
  {% break %}
   {% endif %} 
{% endfor %}



</div>
