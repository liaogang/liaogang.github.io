---
layout: post_center_text  
title: Tweet
permalink: /tweet/
---

<div >
  {% for post in site.posts %}
  {% if post.tag == 'tweet' %}
    <div class="content">{{ post.date | date: "%Y-%m-%d" }}  {{ post.content }}</div>
  {% endif %}{% endfor %}
</div>
