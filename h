[33mcommit f5da4843c4e76549e3ec0d9d6a4347f6d2e638b0[m[33m ([m[1;36mHEAD -> [m[1;32mmain[m[33m, [m[1;31morigin/devise-update[m[33m, [m[1;32mdevise-update[m[33m)[m
Author: Ved Tiwari <ved@webkorps.com>
Date:   Tue Oct 18 20:23:40 2022 +0530

    add validations in car_number , in_time and out time , Add user confirmation for customer booking

[1mdiff --git a/Gemfile b/Gemfile[m
[1mindex 68120bf..fd7cda1 100644[m
[1m--- a/Gemfile[m
[1m+++ b/Gemfile[m
[36m@@ -7,6 +7,8 @@[m [mruby '3.0.0'[m
 gem 'better_errors'[m
 gem 'devise'[m
 gem 'email_validator'[m
[32m+[m
[32m+[m[32m# gem "letter_opener"[m
 # gem 'cancancan'[m
 # Bundle edge Rails instead: gem "rails", github: "rails/rails", branch: "main"[m
 gem 'rails', '~> 7.0.4'[m
[1mdiff --git a/Gemfile.lock b/Gemfile.lock[m
[1mindex 5a8b474..2ad3309 100644[m
[1m--- a/Gemfile.lock[m
[1m+++ b/Gemfile.lock[m
[36m@@ -118,6 +118,10 @@[m [mGEM[m
       actionview (>= 5.0.0)[m
       activesupport (>= 5.0.0)[m
     json (2.6.2)[m
[32m+[m[32m    launchy (2.5.0)[m
[32m+[m[32m      addressable (~> 2.7)[m
[32m+[m[32m    letter_opener (1.8.1)[m
[32m+[m[32m      launchy (>= 2.2, < 3)[m
     loofah (2.19.0)[m
       crass (~> 1.0.2)[m
       nokogiri (>= 1.5.9)[m
[36m@@ -262,6 +266,7 @@[m [mDEPENDENCIES[m
   email_validator[m
   importmap-rails[m
   jbuilder[m
[32m+[m[32m  letter_opener[m
   puma (~> 5.0)[m
   rails (~> 7.0.4)[m
   rubocop[m
[1mdiff --git a/app/controllers/homes_controller.rb b/app/controllers/homes_controller.rb[m
[1mindex 595eaa7..aa37035 100644[m
[1m--- a/app/controllers/homes_controller.rb[m
[1m+++ b/app/controllers/homes_controller.rb[m
[36m@@ -3,5 +3,7 @@[m
 class HomesController < ApplicationController[m
   before_action :authenticate_user![m
 [m
[31m-  def index; end[m
[32m+[m[32m  def index[m
[32m+[m[32m    @user = User.all[m
[32m+[m[32m  end[m
 end[m
[1mdiff --git a/app/controllers/user_details_controller.rb b/app/controllers/user_details_controller.rb[m
[1mindex 1b45572..2704022 100644[m
[1m--- a/app/controllers/user_details_controller.rb[m
[1m+++ b/app/controllers/user_details_controller.rb[m
[36m@@ -17,8 +17,9 @@[m [mclass UserDetailsController < ApplicationController[m
 [m
   def update[m
     if @ud.update(ud_params)[m
[32m+[m[32m      UserDetailMailer.booking_confirmation(@ud, current_user).deliver_later[m
       flash[:notice] = 'Details Updated'[m
[31m-      redirect_to @ud[m
[32m+[m[32m      redirect_to root_path[m
     else[m
       render 'edit', status: :unprocessable_entity[m
     end[m
[36m@@ -47,7 +48,7 @@[m [mclass UserDetailsController < ApplicationController[m
   private[m
 [m
   def ud_params[m
[31m-    params.require(:user_detail).permit(:name, :email, :car_color, :car_number, :in_time, :out_time, :slot_id)[m
[32m+[m[32m    params.require(:user_detail).permit(:name, :email, :car_color, :car_number, :in_time, :out_time, :slot_id, :confirm)[m
   end[m
 [m
   def set_ud[m
[1mdiff --git a/app/mailers/user_detail_mailer.rb b/app/mailers/user_detail_mailer.rb[m
[1mindex 3d6f698..6439d13 100644[m
[1m--- a/app/mailers/user_detail_mailer.rb[m
[1m+++ b/app/mailers/user_detail_mailer.rb[m
[36m@@ -8,6 +8,6 @@[m [mclass UserDetailMailer < ApplicationMailer[m
   #[m
   def booking_confirmation(user_detail, user)[m
     @ud = user_detail[m
[31m-    mail to: user.email, subject: 'Booking Confirmation'[m
[32m+[m[32m    mail to: user.email, subject: 'Regarding Booking Confirmation'[m
   end[m
 end[m
[1mdiff --git a/app/models/user_detail.rb b/app/models/user_detail.rb[m
[1mindex 9ebf947..3050bd7 100644[m
[1m--- a/app/models/user_detail.rb[m
[1m+++ b/app/models/user_detail.rb[m
[36m@@ -1,12 +1,29 @@[m
 # frozen_string_literal: true[m
 [m
[32m+[m[32m# usermodel[m
 class UserDetail < ApplicationRecord[m
   belongs_to :slot[m
 [m
   validates :name, :car_color, presence: true, length: { maximum: 30 }[m
 [m
[31m-  validates :in_time, :out_time, presence: true[m
[32m+[m[32m  validates :in_time, presence: true[m
[32m+[m
[32m+[m[32m  validates_comparison_of :in_time, greater_than_or_equal_to: Time.now.strftime('%d/%m/%Y %H:%M')[m
[32m+[m
[32m+[m[32m  validates :out_time, presence: true[m
 [m
   validates :car_number, uniqueness: true, presence: true,[m
                          format: { with: /\A([A-Z]{2})+[0-9]{2}+[A-Z]{2}+[0-9]{4}\z/i }[m
[32m+[m
[32m+[m[32m  validate :out_time_is_after_in_time[m
[32m+[m
[32m+[m[32m  private[m
[32m+[m
[32m+[m[32m  def out_time_is_after_in_time[m
[32m+[m[32m    if out_time < in_time[m
[32m+[m[32m      errors.add(:out_time, 'cannt be before the in time')[m
[32m+[m[32m    end[m
[32m+[m[32m  end[m
 end[m
[32m+[m
[32m+[m[32m# validates_comparison_of :in_time, greater_than: Time.now.strftime()[m
[1mdiff --git a/app/views/homes/index.html.erb b/app/views/homes/index.html.erb[m
[1mindex 50063b1..b452867 100644[m
[1m--- a/app/views/homes/index.html.erb[m
[1m+++ b/app/views/homes/index.html.erb[m
[36m@@ -2,6 +2,48 @@[m
 <strong>Email:</strong> <%= current_user.email  if current_user%>[m
 [m
 [m
[32m+[m[32m<%if current_user.admin %>[m
[32m+[m[32m<head>[m
[32m+[m[32m  <style>[m
[32m+[m[32m         table, th, td {[m
[32m+[m[32m            border: 1px solid black;[m
[32m+[m[32m            font-family: "Times New Roman", Times, serif;[m
[32m+[m[32m         }[m[41m      [m
[32m+[m[32m  </style>[m
[32m+[m[32m</head>[m[41m  [m
[32m+[m
[32m+[m[32m<body>[m
[32m+[m[32m<table>[m
[32m+[m[32m  <thead>[m
[32m+[m[32m  </tr>[m
[32m+[m[32m      <th style="width:100px">Name</th>[m
[32m+[m[32m      <th style="width:250px">Email</th>[m
[32m+[m[32m      <th style="width:350px">admin</th>[m
[32m+[m[32m    </tr>[m
[32m+[m[32m  </thead>[m
[32m+[m
[32m+[m[32m  <tbody>[m
[32m+[m[32m    <% @user.each do |u| %>[m
[32m+[m[32m      <tr>[m
[32m+[m[32m        <td><%= u.name %></td>[m
[32m+[m[32m        <td><%= u.email %></td>[m
[32m+[m[32m        <% if u.admin==true %>[m
[32m+[m[32m          <td><%= "Admin"%></td>[m
[32m+[m[32m        <%else%>[m
[32m+[m[32m           <td><%= "Customer" %></td>[m
[32m+[m[32m        <%end%>[m
[32m+[m[32m      </tr>[m
[32m+[m[32m    <% end %>[m
[32m+[m[41m    [m
[32m+[m[32m  </tbody>[m
[32m+[m[32m</table>[m
[32m+[m[32m</body>[m
[32m+[m[32m<%end%>[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m
 <%[m
 =begin%>[m
  [m
[1mdiff --git a/app/views/user_detail_mailer/booking_confirmation.html.erb b/app/views/user_detail_mailer/booking_confirmation.html.erb[m
[1mindex 70eb0fe..f6606ba 100644[m
[1m--- a/app/views/user_detail_mailer/booking_confirmation.html.erb[m
[1m+++ b/app/views/user_detail_mailer/booking_confirmation.html.erb[m
[36m@@ -1,7 +1,11 @@[m
 [m
 [m
[32m+[m[32m<%if @ud.confirm.nil? %>[m
[32m+[m[32m   Hii <%= @ud.name %> your booking request has been sent to Admin. Wait till it is confirmed.[m
[32m+[m[32m  <strong><p>Booking Panding....</p></strong>[m
[32m+[m[41m  [m
[32m+[m[32m<%else%>[m[41m  [m
 Congratulation <%= @ud.name %> Parking slot successfully booked.You can park your car.[m
[31m-[m
 <ul>[m
 <% m= @ud.out_time %>[m
 <% n= @ud.in_time %>[m
[36m@@ -9,5 +13,6 @@[m [mCongratulation <%= @ud.name %> Parking slot successfully booked.You can park you[m
 <li><strong>Floor: <strong><%= @ud.slot.floor_id%></li>[m
 <li><strong>Price: <strong><%= (((m-n)/1.hours).round)*100%></li>[m
 </ul>[m
[32m+[m[32m<%end%>[m
 [m
 Thankyou[m
\ No newline at end of file[m
[1mdiff --git a/app/views/user_details/edit.html.erb b/app/views/user_details/edit.html.erb[m
[1mindex f3fb1f2..abab0d4 100644[m
[1m--- a/app/views/user_details/edit.html.erb[m
[1m+++ b/app/views/user_details/edit.html.erb[m
[36m@@ -1,7 +1,13 @@[m
 <div class= "col-lg-6 mx-lg-auto">[m
 <div class="card shadow">[m
 <div class="card-header" style="background-color:DodgerBlue;">[m
[32m+[m[32m<% if @ud.confirm.nil?%>[m
[32m+[m[32m<h2 class="card-title">Pending Request</h2>[m
[32m+[m[32m<% else%>[m
 <h2 class="card-title">Edit Details</h2>[m
[32m+[m[32m<%end%>[m
[32m+[m
[32m+[m
 </div>[m
 <div class="card-body">[m
 [m
[36m@@ -15,6 +21,18 @@[m
 <% end %>[m
 [m
 <%= form_with(model: @ud, local: true) do |f| %>[m
[32m+[m
[32m+[m[32m  <% if @ud.confirm.nil?%>[m
[32m+[m[32m   <p>[m[41m [m
[32m+[m[32m    <%= f.hidden_field :confirm, Placeholder: "Enter Comment ", value: "approved", autofocus: true, class: "form-control form-control-lg"%>[m
[32m+[m[32m  </p>[m
[32m+[m
[32m+[m[32m  <p>[m
[32m+[m[32m    <%= f.submit 'Confirm', class: "btn btn-primary"%>[m
[32m+[m[32m  </p>[m
[32m+[m[41m [m
[32m+[m[32m  <%else%>[m
[32m+[m
   <p> [m
     <%= f.label :name, class: 'mb-2'  %>[m
     <%= f.text_field :name,Placeholder: "Enter name", autofocus: true, class: "form-control form-control-lg" %>[m
[36m@@ -45,12 +63,17 @@[m
     <%= f.number_field :slot_id , class: "form-control form-control-lg"%>[m
   </p> [m
 [m
[32m+[m[32m  <p>[m[41m [m
[32m+[m[32m    <%= f.label :confirm, class: 'mb-2'  %>[m
[32m+[m[32m    <%= f.text_field :confirm, Placeholder: "Enter Comment ", autofocus: true, class: "form-control form-control-lg"%>[m
[32m+[m[32m  </p>[m
[32m+[m[41m  [m
[32m+[m
   <p>[m
     <%= f.submit 'submit', class: "btn btn-primary"%>[m
   </p>[m
[32m+[m[32m  <%end%>[m
 <% end %>[m
[31m-<button><%= link_to 'back', user_details_path %></button>[m
[31m-[m
 [m
 </div>[m
 </div>[m
[1mdiff --git a/app/views/user_details/index.html.erb b/app/views/user_details/index.html.erb[m
[1mindex 09f6582..254c6d0 100644[m
[1m--- a/app/views/user_details/index.html.erb[m
[1m+++ b/app/views/user_details/index.html.erb[m
[36m@@ -1,50 +1,62 @@[m
[32m+[m
 <head>[m
   <style>[m
[31m-[m
[31m-  .card{[m
[31m-  padding: 10px;[m
[31m-  margin: 15px;[m
[31m-  height: inline-block;[m
[31m-  box-shadow: 0px 0px 3px 2px green;[m
[31m-  width: fit-content;[m
[31m-  display: inline-block;[m
[31m-  /* float:left; */[m
[31m-  }[m
[31m-[m
[31m-  p{[m
[31m-  line-height: 20px;[m
[31m-  }[m
[31m-  .btn-field{[m
[31m-  display: flex;[m
[31m-  }[m
[31m-[m
[32m+[m[32m         table, th, td {[m
[32m+[m[32m            border: 1px solid black;[m
[32m+[m[32m            font-family: "Times New Roman", Times, serif;[m
[32m+[m[32m         }[m[41m      [m
   </style>[m
 </head>  [m
[32m+[m
 <body>[m
[31m-  <div class="wrap">[m
[31m-    <h3>Booking</h3>[m
[32m+[m[32m<table>[m
[32m+[m[32m  <thead>[m
[32m+[m[32m  </tr>[m
[32m+[m[32m      <th style="width:100px">Name</th>[m
[32m+[m[32m      <th style="width:250px">car_number</th>[m
[32m+[m[32m      <th style="width:350px">car_color</th>[m
[32m+[m[32m      <th style="width:450px">in_time</th>[m
[32m+[m[32m      <th style="width:450px">out_time</th>[m
[32m+[m[32m      <th style="width:350px">slot_id</th>[m
[32m+[m[32m      <th style="width:350px">floor</th>[m
[32m+[m[32m      <th style="width:350px">status</th>[m
[32m+[m[32m      <th style="width:auto" colspan= "3">Action</th>[m
[32m+[m
[32m+[m[32m    </tr>[m
[32m+[m[32m  </thead>[m
[32m+[m
[32m+[m[32m  <tbody>[m
[32m+[m[41m    [m
[32m+[m
[32m+[m
     <% @ud.each do |user| %>[m
[31m-      [m
[32m+[m[32m    <tr>[m
         <% if  current_user.admin || user.name == current_user.name %>[m
[31m-      <div class="card">[m
[31m-          <p><strong>Name: </strong><%= user.name %></p>[m
[31m-          <p><strong>Car Number: </strong><%= user.car_number %></p>[m
[31m-          <p><strong>Car Color: </strong><%= user.car_color %></p>[m
[31m-          <p><strong>In Time: </strong><%= user.in_time %></p>[m
[31m-          <p><strong>Out Time: </strong><%= user.out_time %></p>[m
[31m-          <p><strong>Slot Id: </strong><%= user.slot_id%></p>[m
[31m-           <p><strong>Floor Id: </strong><%= user.slot.floor_id%></p>[m
[31m-          <button><%= link_to 'Show', user_detail_path(user) %></button>[m
[31m-[m
[32m+[m[32m          <td><%= user.name %></td>[m
[32m+[m[32m          <td><%= user.car_number %></td>[m
[32m+[m[32m          <td><%= user.car_color %></td>[m
[32m+[m[32m          <td><%= user.in_time %></td>[m
[32m+[m[32m          <td><%= user.out_time %></td>[m
[32m+[m[32m          <td><%= user.slot_id%></td>[m
[32m+[m[32m          <td><%= user.slot.floor_id%></td>[m
[32m+[m[32m          <td> <%= user.confirm.nil? ? "Pending" : "Booked"%></td>[m
[32m+[m[32m          <td><button><%= link_to 'Show', user_detail_path(user) %></button>[m
           <% if  current_user.admin %>[m
[31m-              <%= link_to 'Delete', user_detail_path(user),data: {turbo_method: :delete, turbo_confirm: "Are you sure?"} %>|[m
[31m-              <%= link_to 'Edit', edit_user_detail_path(user) %>[m
[32m+[m[32m              <td><button><%= link_to 'Delete', user_detail_path(user),data: {turbo_method: :delete, turbo_confirm: "Are you sure?"} %></button></td>[m
[32m+[m[32m              <% if user.confirm.nil?%>[m
[32m+[m[41m              [m
[32m+[m[32m                <td><button><%= link_to 'PendingRequest', edit_user_detail_path(user) %></button></td>[m
[32m+[m[32m              <%else%>[m
[32m+[m[32m                <td><button><%= link_to 'Edit', edit_user_detail_path(user) %></button></td>[m
[32m+[m[32m              <%end%>[m
           <% end %>[m
         <% end %>[m
[31m-      </div>[m
[32m+[m[32m      </tr>[m
     <% end %>[m
[31m-    <button><%= link_to 'back', root_path %></button>[m
[31m-  </div>[m
[32m+[m[41m  [m
[32m+[m[41m    [m
[32m+[m[32m  </tbody>[m
[32m+[m[32m</table>[m
 </body>[m
 [m
 [m
[36m@@ -60,12 +72,6 @@[m
 [m
 [m
 [m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
 [m
 [m
 [m
[36m@@ -75,6 +81,8 @@[m
 <%[m
 =begin%>[m
  <p>[m
[32m+[m[32m     <button><%= link_to 'back', root_path %></button>[m
[32m+[m
   <%= link_to 'Create new users ', new_user_path %></br>[m
   <%= link_to 'return to user prog', users_path %>[m
 </p> [m
[1mdiff --git a/app/views/user_details/show.html.erb b/app/views/user_details/show.html.erb[m
[1mindex 3571ce6..abc19ac 100644[m
[1m--- a/app/views/user_details/show.html.erb[m
[1m+++ b/app/views/user_details/show.html.erb[m
[36m@@ -12,13 +12,17 @@[m
 <p><strong>Out Time: </strong><%= @ud.out_time %></p>[m
 <p><strong>Slot Id: </strong><%= @ud.slot_id%></p>[m
 <p><strong>Floor : </strong><%= @ud.slot.floor_id%></p>[m
[32m+[m[32m<%if @ud.confirm.nil? %>[m
[32m+[m[32m   <p><strong>Status : </strong><%= "Pending"%><p>[m
[32m+[m[32m<%else%>[m[41m   [m
[32m+[m[32m  <p><strong>Status : </strong><%= "Booked"%><p>[m
[32m+[m[32m<%end%>[m
[32m+[m
 [m
[31m-<ul>[m
 <% m= @ud.out_time %>[m
 <% n= @ud.in_time %>[m
[31m-<li><strong>Bill Amount: <strong><%= (((m-n)/1.hours).round)*100%></li>[m
[31m-</ul> [m
[31m-<button><%= link_to "back", new_user_registration_path %></button>[m
[32m+[m[32m<strong>Bill Amount: <strong><%= (((m-n)/1.hours).round)*100%>[m
[32m+[m
 [m
 [m
 [m
[36m@@ -28,6 +32,8 @@[m
 [m
 <%[m
 =begin%>[m
[32m+[m[32m<button><%= link_to "back", new_user_registration_path %></button>[m
[32m+[m
  <%= @ud.floor.number_of_floor if @ud.floor %>[m
  <%= link_to 'Delete', user_detail_path,data: {turbo_method: :delete, turbo_confirm: "Are you sure?"}%>[m
 <%= link_to 'return to userdetail', user_details_path %> [m
[1mdiff --git a/config/environments/development.rb b/config/environments/development.rb[m
[1mindex c0aa323..d33a487 100644[m
[1m--- a/config/environments/development.rb[m
[1m+++ b/config/environments/development.rb[m
[36m@@ -2,6 +2,7 @@[m
 [m
 require 'active_support/core_ext/integer/time'[m
 [m
[32m+[m[32m# application[m
 Rails.application.configure do[m
   # Settings specified here will take precedence over those in config/application.rb.[m
 [m
[36m@@ -82,4 +83,6 @@[m [mRails.application.configure do[m
   }[m
   config.exceptions_app = routes[m
   config.action_mailer.perform_deliveries = true[m
[32m+[m
[32m+[m
 end[m
[1mdiff --git a/db/migrate/20220922194615_create_user_details.rb b/db/migrate/20220922194615_create_user_details.rb[m
[1mindex 7019e87..d15be39 100644[m
[1m--- a/db/migrate/20220922194615_create_user_details.rb[m
[1m+++ b/db/migrate/20220922194615_create_user_details.rb[m
[36m@@ -9,7 +9,8 @@[m [mclass CreateUserDetails < ActiveRecord::Migration[7.0][m
       t.string :car_number[m
       t.datetime :in_time[m
       t.datetime :out_time[m
[31m-[m
[32m+[m[32m      t.string :confirm[m
[32m+[m[41m      [m
       t.timestamps[m
     end[m
   end[m
[1mdiff --git a/db/schema.rb b/db/schema.rb[m
[1mindex c015f0f..fdca5ea 100644[m
[1m--- a/db/schema.rb[m
[1m+++ b/db/schema.rb[m
[36m@@ -1,5 +1,3 @@[m
[31m-# frozen_string_literal: true[m
[31m-[m
 # This file is auto-generated from the current state of the database. Instead[m
 # of editing this file, please use the migrations feature of Active Record to[m
 # incrementally modify your database, and then regenerate this schema definition.[m
[36m@@ -12,47 +10,49 @@[m
 #[m
 # It's strongly recommended that you check this file into your version control system.[m
 [m
[31m-ActiveRecord::Schema[7.0].define(version: 20_221_013_201_904) do[m
[31m-  create_table 'floors', force: :cascade do |t|[m
[31m-    t.integer 'number_of_floor'[m
[31m-    t.datetime 'created_at', null: false[m
[31m-    t.datetime 'updated_at', null: false[m
[32m+[m[32mActiveRecord::Schema[7.0].define(version: 2022_10_13_201904) do[m
[32m+[m[32m  create_table "floors", force: :cascade do |t|[m
[32m+[m[32m    t.integer "number_of_floor"[m
[32m+[m[32m    t.datetime "created_at", null: false[m
[32m+[m[32m    t.datetime "updated_at", null: false[m
   end[m
 [m
[31m-  create_table 'slots', force: :cascade do |t|[m
[31m-    t.integer 'slot_number'[m
[31m-    t.datetime 'created_at', null: false[m
[31m-    t.datetime 'updated_at', null: false[m
[31m-    t.integer 'floor_id'[m
[32m+[m[32m  create_table "slots", force: :cascade do |t|[m
[32m+[m[32m    t.integer "slot_number"[m
[32m+[m[32m    t.datetime "created_at", null: false[m
[32m+[m[32m    t.datetime "updated_at", null: false[m
[32m+[m[32m    t.integer "floor_id"[m
   end[m
 [m
[31m-  create_table 'user_details', force: :cascade do |t|[m
[31m-    t.string 'name'[m
[31m-    t.string 'car_color'[m
[31m-    t.string 'car_number'[m
[31m-    t.datetime 'in_time'[m
[31m-    t.datetime 'out_time'[m
[31m-    t.datetime 'created_at', null: false[m
[31m-    t.datetime 'updated_at', null: false[m
[31m-    t.integer 'slot_id'[m
[32m+[m[32m  create_table "user_details", force: :cascade do |t|[m
[32m+[m[32m    t.string "name"[m
[32m+[m[32m    t.string "car_color"[m
[32m+[m[32m    t.string "car_number"[m
[32m+[m[32m    t.datetime "in_time"[m
[32m+[m[32m    t.datetime "out_time"[m
[32m+[m[32m    t.string "confirm"[m
[32m+[m[32m    t.datetime "created_at", null: false[m
[32m+[m[32m    t.datetime "updated_at", null: false[m
[32m+[m[32m    t.integer "slot_id"[m
   end[m
 [m
[31m-  create_table 'users', force: :cascade do |t|[m
[31m-    t.string 'email', default: '', null: false[m
[31m-    t.string 'encrypted_password', default: '', null: false[m
[31m-    t.string 'name'[m
[31m-    t.string 'reset_password_token'[m
[31m-    t.datetime 'reset_password_sent_at'[m
[31m-    t.datetime 'remember_created_at'[m
[31m-    t.integer 'sign_in_count', default: 0, null: false[m
[31m-    t.datetime 'current_sign_in_at'[m
[31m-    t.datetime 'last_sign_in_at'[m
[31m-    t.string 'current_sign_in_ip'[m
[31m-    t.string 'last_sign_in_ip'[m
[31m-    t.datetime 'created_at', null: false[m
[31m-    t.datetime 'updated_at', null: false[m
[31m-    t.boolean 'admin', default: false[m
[31m-    t.index ['email'], name: 'index_users_on_email', unique: true[m
[31m-    t.index ['reset_password_token'], name: 'index_users_on_reset_password_token', unique: true[m
[32m+[m[32m  create_table "users", force: :cascade do |t|[m
[32m+[m[32m    t.string "email", default: "", null: false[m
[32m+[m[32m    t.string "encrypted_password", default: "", null: false[m
[32m+[m[32m    t.string "name"[m
[32m+[m[32m    t.string "reset_password_token"[m
[32m+[m[32m    t.datetime "reset_password_sent_at"[m
[32m+[m[32m    t.datetime "remember_created_at"[m
[32m+[m[32m    t.integer "sign_in_count", default: 0, null: false[m
[32m+[m[32m    t.datetime "current_sign_in_at"[m
[32m+[m[32m    t.datetime "last_sign_in_at"[m
[32m+[m[32m    t.string "current_sign_in_ip"[m
[32m+[m[32m    t.string "last_sign_in_ip"[m
[32m+[m[32m    t.datetime "created_at", null: false[m
[32m+[m[32m    t.datetime "updated_at", null: false[m
[32m+[m[32m    t.boolean "admin", default: false[m
[32m+[m[32m    t.index ["email"], name: "index_users_on_email", unique: true[m
[32m+[m[32m    t.index ["reset_password_token"], name: "index_users_on_reset_password_token", unique: true[m
   end[m
[32m+[m
 end[m
[1mdiff --git a/vendor/bundle/ruby/3.0.0/bin/launchy b/vendor/bundle/ruby/3.0.0/bin/launchy[m
[1mnew file mode 100755[m
[1mindex 0000000..943e402[m
[1m--- /dev/null[m
[1m+++ b/vendor/bundle/ruby/3.0.0/bin/launchy[m
[36m@@ -0,0 +1,27 @@[m
[32m+[m[32m#!/usr/bin/env ruby_executable_hooks[m
[32m+[m[32m#[m
[32m+[m[32m# This file was generated by RubyGems.[m
[32m+[m[32m#[m
[32m+[m[32m# The application 'launchy' is installed as part of a gem, and[m
[32m+[m[32m# this file is here to facilitate running it.[m
[32m+[m[32m#[m
[32m+[m
[32m+[m[32mrequire 'rubygems'[m
[32m+[m
[32m+[m[32mversion = ">= 0.a"[m
[32m+[m
[32m+[m[32mstr = ARGV.first[m
[32m+[m[32mif str[m
[32m+[m[32m  str = str.b[/\A_(.*)_\z/, 1][m
[32m+[m[32m  if str and Gem::Version.correct?(str)[m
[32m+[m[32m    version = str[m
[32m+[m[32m    ARGV.shift[m
[32m+[m[32m  end[m
[32m+[m[32mend[m
[32m+[m
[32m+[m[32mif Gem.respond_to?(:activate_bin_path)[m
[32m+[m[32mload Gem.activate_bin_path('launchy', 'launchy', version)[m
[32m+[m[32melse[m
[32m+[m[32mgem "launchy", version[m
[32m+[m[32mload Gem.bin_path("launchy", "launchy", version)[m
[32m+[m[32mend[m
[1mdiff --git a/vendor/bundle/ruby/3.0.0/cache/launchy-2.5.0.gem b/vendor/bundle/ruby/3.0.0/cache/launchy-2.5.0.gem[m
[1mnew file mode 100644[m
[1mindex 0000000..f2f1ced[m
Binary files /dev/null and b/vendor/bundle/ruby/3.0.0/cache/launchy-2.5.0.gem differ
[1mdiff --git a/vendor/bundle/ruby/3.0.0/cache/letter_opener-1.8.1.gem b/vendor/bundle/ruby/3.0.0/cache/letter_opener-1.8.1.gem[m
[1mnew file mode 100644[m
[1mindex 0000000..596e92a[m
Binary files /dev/null and b/vendor/bundle/ruby/3.0.0/cache/letter_opener-1.8.1.gem differ
[1mdiff --git a/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/CONTRIBUTING.md b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/CONTRIBUTING.md[m
[1mnew file mode 100644[m
[1mindex 0000000..49a3c41[m
[1m--- /dev/null[m
[1m+++ b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/CONTRIBUTING.md[m
[36m@@ -0,0 +1,60 @@[m
[32m+[m[32m# Hi there![m
[32m+[m
[32m+[m[32mI see you are interested in contributing. That is wonderful. I love[m
[32m+[m[32mcontributions.[m
[32m+[m
[32m+[m[32mI guarantee that there are bugs in this software. And I guarantee that there is[m
[32m+[m[32ma feature you want that is not in here yet. As such, any and all bugs reports[m
[32m+[m[32mare gratefully accepted, bugfixes even more so. Helping out with bugs is the[m
[32m+[m[32measiest way to contribute.[m
[32m+[m
[32m+[m
[32m+[m[32m## The Quick Version[m
[32m+[m
[32m+[m[32m* Have a [GitHub Account][].[m
[32m+[m[32m* Search the [GitHub Issues][] and see if your issue already present. If so[m
[32m+[m[32m  add your comments, :thumbsup:, etc.[m
[32m+[m[32m* Issue not there? Not a problem, open up a [new issue][].[m
[32m+[m[32m    * **Bug reports** please be as detailed as possible. Include:[m
[32m+[m[32m        * full ruby engine and version: `ruby -e 'puts RUBY_DESCRIPTION'`[m
[32m+[m[32m        * operating system and version[m
[32m+[m[32m        * version of launchy `ruby -rubygems -Ilib -e "require 'launchy'; puts Launchy::VERSION"`[m
[32m+[m[32m        * as much detail about the bug as possible so I can replicate it. Feel free[m
[32m+[m[32m          to link in a [gist][][m
[32m+[m[32m    * **New Feature**[m
[32m+[m[32m        * What the new feature should do.[m
[32m+[m[32m        * What benefit the new feature brings to the project.[m
[32m+[m[32m* Fork the [repo][].[m
[32m+[m[32m* Create a new branch for your issue: `git checkout -b issue/my-issue`[m
[32m+[m[32m* Lovingly craft your contribution:[m
[32m+[m[32m    * `rake develop` to get started[m
[32m+[m[32m    * `bundle exec rake test` to run tests[m
[32m+[m[32m* Make sure that `bundle exec rake test` passes. It's important, I said it twice.[m
[32m+[m[32m* Add yourself to the contributors section below.[m
[32m+[m[32m* Submit your [pull request][].[m
[32m+[m
[32m+[m[32m# Contributors[m
[32m+[m
[32m+[m[32m* [Jeremy Hinegardner](https://github.com/copiousfreetime)[m
[32m+[m[32m* [Mike Farmer](https://github.com/mikefarmer)[m
[32m+[m[32m* [Suraj N. Kurapati](https://github.com/sunaku)[m
[32m+[m[32m* [Postmodern](https://github.com/postmodern)[m
[32m+[m[32m* [Stephen Judkins](https://github.com/stephenjudkins)[m
[32m+[m[32m* [Mariusz Pietrzyk](https://github.com/wijet)[m
[32m+[m[32m* [Bogdan Gusiev](https://github.com/bogdan)[m
[32m+[m[32m* [Miquel Rodríguez Telep](https://github.com/mrtorrent)[m
[32m+[m[32m* [Chris Schmich](https://github.com/schmich)[m
[32m+[m[32m* [Gioele Barabucci](https://github.com/gioele)[m
[32m+[m[32m* [Colin Noel Bell](https://github.com/colbell)[m
[32m+[m[32m* [Mark J. Lehman](https://github.com/supremebeing7)[m
[32m+[m[32m* [Cédric Félizard](https://github.com/infertux)[m
[32m+[m[32m* [Daniel Farina](https://github.com/fdr)[m
[32m+[m[32m* [Jack Turnbull](https://github.com/jackturnbull)[m
[32m+[m[32m* [Jeremy Moritz](https://github.com/jeremymoritz)[m
[32m+[m
[32m+[m[32m[GitHub Account]: https://github.com/signup/free "GitHub Signup"[m
[32m+[m[32m[GitHub Issues]:  https://github.com/copiousfreetime/launchy/issues "Launchy Issues"[m
[32m+[m[32m[new issue]:      https://github.com/copiousfreetime/launchy/issues/new "New Launchy Issue"[m
[32m+[m[32m[gist]:           https://gist.github.com/ "New Gist"[m
[32m+[m[32m[repo]:           https://github.com/copiousfreetime/launchy "Launchy Repo"[m
[32m+[m[32m[pull request]:   https://help.github.com/articles/using-pull-requests "Using Pull Requests"[m
[1mdiff --git a/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/HISTORY.md b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/HISTORY.md[m
[1mnew file mode 100644[m
[1mindex 0000000..88e7a29[m
[1m--- /dev/null[m
[1m+++ b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/HISTORY.md[m
[36m@@ -0,0 +1,168 @@[m
[32m+[m[32m# Launchy Changelog[m
[32m+[m
[32m+[m[32m## Version 2.5.0 - 2020-02-27[m
[32m+[m[32m* Update depedencies[m
[32m+[m[32m* Update minimum ruby level[m
[32m+[m[32m* Move to `kde-open` on KDE - <https://github.com/copiousfreetime/launchy/pull/105> - wstephenson[m
[32m+[m[32m* Applied some grammer / spelling fixes - <https://github.com/copiousfreetime/launchy/pull/130> - jeremymoritz[m
[32m+[m[32m* `Pathname` instances do not raise exceptions when opening local files - <https://github.com/copiousfreetime/launchy/issues/101> - dmke[m
[32m+[m[32m* Add a fallback console browsers - <https://github.com/copiousfreetime/launchy/issues/93> - trejkaz[m
[32m+[m
[32m+[m[32m## Version 2.4.3 - 2014-11-03[m
[32m+[m[32m* Update documentation - <https://github.com/copiousfreetime/launchy/pull/81> - supremebeing7[m
[32m+[m[32m* Fix launching of `exo-open` for XFCE - <https://github.com/copiousfreetime/launchy/issues/82> - dsandstrom[m
[32m+[m[32m* Add iceweasel as a fallback browser - <https://github.com/copiousfreetime/launchy/pull/92> -  jackturnbull[m
[32m+[m[32m* Reopen $stderr in really bad situation - <https://github.com/copiousfreetime/launchy/pull/77> - infertux[m
[32m+[m
[32m+[m[32m## Version 2.4.2 - 2013-11-28[m
[32m+[m[32m* Fix kde issue - <https://github.com/copiousfreetime/launchy/issues/72> - colbell[m
[32m+[m
[32m+[m[32m## Version 2.4.1 - 2013-11-26[m
[32m+[m[32m* Abstract out the argv of the commandline - <https://github.com/copiousfreetime/launchy/issues/71>[m
[32m+[m
[32m+[m[32m## Version 2.4.0 - 2013-11-12[m
[32m+[m[32m* Support `Launchy.open( url, :debug => true )` - <http://github.com/copiousfreetime/launchy/issues/63> - schmich[m
[32m+[m[32m* Fix inconsistencies in `debug?` and `dry_run?` methods - <http://github.com/copiousfreetime/launchy/issues/63> - schmich[m
[32m+[m[32m* Fix detection of missing *nix desktops - <http://github.com/copiousfreetime/launchy/issues/70>[m
[32m+[m[32m* Fix running tests in bare Linux environment - <http://github.com/copiousfreetime/launchy/issues/67> - gioele[m
[32m+[m[32m* Fix mistaking windows drive as uri schema - <http://github.com/copiousfreetime/launchy/issues/65>[m
[32m+[m[32m* Attempt fixing windows `start` command oddities, again - <http://github.com/copiousfreetime/launchy/issues/62>[m
[32m+[m
[32m+[m[32m## Version 2.3.0 - 2013-04-11[m
[32m+[m
[32m+[m[32m* Add the option to call a block on error instead of raising an exception[m
[32m+[m
[32m+[m[32m## Version 2.2.0 - 2013-02-06[m
[32m+[m
[32m+[m[32m* Change XFCE detection to not depend on grep <http://github.com/copiousfreetime/launchy/issues/52> - bogdan[m
[32m+[m[32m* Suppress forked process output <http://github.com/copiousfreetime/launchy/issues/51>[m
[32m+[m[32m* Display help/usage if no url is given <http://github.com/copiousfreetime/launchy/issues/54>[m
[32m+[m[32m* Detect the fluxbox environment <http://github.com/copiousfreetime/launchy/issues/53>[m
[32m+[m[32m* Automatically detect `http` url's if they are missing the `http://` <http://github.com/copiousfreetime/launchy/issues/55>[m
[32m+[m[32m* Update to latest project management rake tasks[m
[32m+[m
[32m+[m[32m## Version 2.1.2 - 2012-08-06[m
[32m+[m
[32m+[m[32m* Fix where HostOS would fail to convert to string on JRuby in 1.9 mode <http://github.com/copiousfreetime/launchy/issues/45>[m
[32m+[m
[32m+[m[32m## Version 2.1.1 - 2012-07-28[m
[32m+[m
[32m+[m[32m* Update addressable runtime dependency <http://github.com/copiousfreetime/launchy/issues/47>[m
[32m+[m[32m* Bring minitest and ffi development dependencies up to date[m
[32m+[m
[32m+[m[32m## Version 2.1.0 - 2012-03-18[m
[32m+[m
[32m+[m[32m* Fix raising exception when no browser program found <http://github.com/copiousfreetime/launchy/issues/42>[m
[32m+[m[32m* Add `LAUNCHY_DRY_RUN` environment variable (Mariusz Pietrzyk / wijet)[m
[32m+[m[32m* Update dependencies[m
[32m+[m
[32m+[m[32m## Version 2.0.5 - 2011-07-24[m
[32m+[m
[32m+[m[32m* Fix the case where `$BROWSER` is set and no *nix desktop was found <http://github.com/copiousfreetime/launchy/issues/33>[m
[32m+[m
[32m+[m[32m## Version 2.0.4 - 2011-07-23[m
[32m+[m
[32m+[m[32m* Fix windows `start` commandline <http://github.com/copiousfreetime/launchy/issues/5>[m
[32m+[m[32m* Add capability to open local files with no file: scheme present <http://github.com/copiousfreetime/launchy/issues/29>[m
[32m+[m[32m* Added `rake how_to_contribute` task <http://github.com/copiousfreetime/launchy/issues/30>[m
[32m+[m[32m* Make better decisions on when to do shell escaping <http://github.com/copiousfreetime/launchy/issues/31>[m
[32m+[m[32m* Switch to Addressable::URI so UTF-8 urls may be parsed. <http://github.com/copiousfreetime/launchy/issues/32>[m
[32m+[m
[32m+[m[32m## Version 2.0.3 - 2011-07-17[m
[32m+[m
[32m+[m[32m* Add in Deprecated API wrappers that warn the user[m
[32m+[m
[32m+[m[32m## Version 2.0.2 - 2011-07-17[m
[32m+[m
[32m+[m[32m* Typo fixes from @mtorrent[m
[32m+[m[32m* Documentation updates explicitly stating the Public API[m
[32m+[m[32m* Increase test coverage[m
[32m+[m
[32m+[m[32m## Version 2.0.1 - 2011-07-16[m
[32m+[m
[32m+[m[32m* Almost a complete rewrite[m
[32m+[m[32m* JRuby Support[m
[32m+[m[32m* Organization is such that it will be easier to add additional applications[m
[32m+[m[32m* Windows behavior possibly fixed, again[m
[32m+[m
[32m+[m[32m## Version 1.0.0 - 2011-03-17[m
[32m+[m
[32m+[m[32m* Add JRuby support (Stephen Judkins)[m
[32m+[m[32m* Remove unused Paths module[m
[32m+[m[32m* Switch to using bones[m
[32m+[m[32m* Switch to use minitest[m
[32m+[m[32m* NOTE, this version was never released.[m
[32m+[m
[32m+[m[32m## Version 0.4.0 - 2011-01-27[m
[32m+[m
[32m+[m[32m* Add support for `file:///` schema (postmodern)[m
[32m+[m
[32m+[m[32m## Version 0.3.7 - 2010-07-19[m
[32m+[m
[32m+[m[32m* Fix launchy on windows (mikefarmer)[m
[32m+[m
[32m+[m[32m## Version 0.3.6 - 2010-02-22[m
[32m+[m
[32m+[m[32m* add a test:spec task to run tests without rcov support[m
[32m+[m[32m* added `testing` os family for running tests[m
[32m+[m
[32m+[m[32m## Version 0.3.5 - 2009-12-17[m
[32m+[m
[32m+[m[32m* clarify that launchy is under ISC license[m
[32m+[m[32m* fix missing data file in released gem needed for running specs[m
[32m+[m
[32m+[m[32m## Version 0.3.3 - 2009-02-19[m
[32m+[m
[32m+[m[32m* pass command line as discrete items to system() to avoid string[m
[32m+[m[32m  interpretation by the system shell. (Suraj N. Kurapati)[m
[32m+[m[32m* rework project layout and tasks[m
[32m+[m
[32m+[m[32m## Version 0.3.2 - 2008-05-21[m
[32m+[m
[32m+[m[32m* detect aix and mingw as known operating systems.[m
[32m+[m
[32m+[m[32m## Version 0.3.1 - 2007-09-08[m
[32m+[m
[32m+[m[32m* finalize the command line wrapper around the launchy library.[m
[32m+[m[32m* added more tests[m
[32m+[m
[32m+[m[32m## Version 0.3.0 - 2007-08-30[m
[32m+[m
[32m+[m[32m* reorganize the code structure, removing Spawnable namespace[m
[32m+[m[32m* removed `do_magic` method, changed it to `open`[m
[32m+[m[32m* added override environment variable LAUNCHY_HOST_OS for testing[m
[32m+[m[32m* fix broken cygwin support [Bug #13472][m
[32m+[m
[32m+[m[32m## Version 0.2.1 - 2007-08-18[m
[32m+[m
[32m+[m[32m* fix inability to find windows executables [Bug #13132][m
[32m+[m
[32m+[m[32m## Version 0.2.0 - 2007-08-11[m
[32m+[m
[32m+[m[32m* rework browser finding[m
[32m+[m[32m* manual override with `LAUNCHY_BROWSER` environment variable[m
[32m+[m[32m* on *nix use desktop application launcher with fallback to list of browsers[m
[32m+[m[32m* On windows, switch to 'start' command and remove dependency on win32-process[m
[32m+[m[32m* removed win32 gem[m
[32m+[m[32m* Add debug output by setting `LAUNCHY_DEBUG` environment variable to `true`[m
[32m+[m
[32m+[m[32m## Version 0.1.2 - 2007-08-11[m
[32m+[m
[32m+[m[32m* forked child exits without calling `at_exit` handlers[m
[32m+[m
[32m+[m[32m## Version 0.1.1[m
[32m+[m
[32m+[m[32m* fixed rubyforge task to release mswin32 gem also[m
[32m+[m
[32m+[m[32m## Version 0.1.0[m
[32m+[m
[32m+[m[32m* Initial public release[m
[32m+[m[32m* switched to using fork to spawn process and `require 'win32/process'` if on windows[m
[32m+[m
[32m+[m[32m## Version 0.0.2[m
[32m+[m
[32m+[m[32m* First attempt at using systemu to spawn processes[m
[32m+[m
[32m+[m[32m## Version 0.0.1[m
[32m+[m
[32m+[m[32m* Initially working release[m
[1mdiff --git a/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/LICENSE b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/LICENSE[m
[1mnew file mode 100644[m
[1mindex 0000000..4f35cf0[m
[1m--- /dev/null[m
[1m+++ b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/LICENSE[m
[36m@@ -0,0 +1,16 @@[m
[32m+[m[32mISC LICENSE - http://opensource.org/licenses/isc-license.txt[m
[32m+[m
[32m+[m[32mCopyright (c) 2007-2020 Jeremy Hinegardner[m
[32m+[m
[32m+[m[32mPermission to use, copy, modify, and/or distribute this software for any[m
[32m+[m[32mpurpose with or without fee is hereby granted, provided that the above[m
[32m+[m[32mcopyright notice and this permission notice appear in all copies.[m
[32m+[m
[32m+[m[32mTHE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES[m
[32m+[m[32mWITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF[m
[32m+[m[32mMERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR[m
[32m+[m[32mANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES[m
[32m+[m[32mWHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN[m
[32m+[m[32mACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF[m
[32m+[m[32mOR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.[m
[32m+[m
[1mdiff --git a/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/Manifest.txt b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/Manifest.txt[m
[1mnew file mode 100644[m
[1mindex 0000000..53307be[m
[1m--- /dev/null[m
[1m+++ b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/Manifest.txt[m
[36m@@ -0,0 +1,38 @@[m
[32m+[m[32mCONTRIBUTING.md[m
[32m+[m[32mHISTORY.md[m
[32m+[m[32mLICENSE[m
[32m+[m[32mManifest.txt[m
[32m+[m[32mREADME.md[m
[32m+[m[32mRakefile[m
[32m+[m[32mbin/launchy[m
[32m+[m[32mlib/launchy.rb[m
[32m+[m[32mlib/launchy/application.rb[m
[32m+[m[32mlib/launchy/applications/browser.rb[m
[32m+[m[32mlib/launchy/argv.rb[m
[32m+[m[32mlib/launchy/cli.rb[m
[32m+[m[32mlib/launchy/deprecated.rb[m
[32m+[m[32mlib/launchy/descendant_tracker.rb[m
[32m+[m[32mlib/launchy/detect.rb[m
[32m+[m[32mlib/launchy/detect/host_os.rb[m
[32m+[m[32mlib/launchy/detect/host_os_family.rb[m
[32m+[m[32mlib/launchy/detect/nix_desktop_environment.rb[m
[32m+[m[32mlib/launchy/detect/ruby_engine.rb[m
[32m+[m[32mlib/launchy/detect/runner.rb[m
[32m+[m[32mlib/launchy/error.rb[m
[32m+[m[32mlib/launchy/os_family.rb[m
[32m+[m[32mlib/launchy/version.rb[m
[32m+[m[32mspec/application_spec.rb[m
[32m+[m[32mspec/applications/browser_spec.rb[m
[32m+[m[32mspec/cli_spec.rb[m
[32m+[m[32mspec/detect/host_os_family_spec.rb[m
[32m+[m[32mspec/detect/host_os_spec.rb[m
[32m+[m[32mspec/detect/nix_desktop_environment_spec.rb[m
[32m+[m[32mspec/detect/ruby_engine_spec.rb[m
[32m+[m[32mspec/detect/runner_spec.rb[m
[32m+[m[32mspec/launchy_spec.rb[m
[32m+[m[32mspec/mock_application.rb[m
[32m+[m[32mspec/spec_helper.rb[m
[32m+[m[32mspec/tattle-host-os.yaml[m
[32m+[m[32mspec/version_spec.rb[m
[32m+[m[32mtasks/default.rake[m
[32m+[m[32mtasks/this.rb[m
[1mdiff --git a/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/README.md b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/README.md[m
[1mnew file mode 100644[m
[1mindex 0000000..65a0f43[m
[1m--- /dev/null[m
[1m+++ b/vendor/bundle/ruby/3.0.0/gems/launchy-2.5.0/README.md[m
[36m@@ -0,0 +1,167 @@[m
[32m+[m[32m# launchy[m
[32m+[m
[32m+[m[32m[![Build Status](https://travis-ci.org/copiousfreetime/launchy.svg?branch=master)](https://travis-ci.org/copiousfreetime/launchy)[m
[32m+[m
[32m+[m
[32m+[m[32m* [Homepage](https://github.com/copiousfreetime/launchy)[m
[32m+[m[32m* [Github Project](https://github.com/copiousfreetime/launchy)[m
[32m+[m
[32m+[m[32m## DESCRIPTION[m
[32m+[m
[32m+[m[32mLaunchy is helper class for launching cross-platform applications in a fire and[m
[32m+[m[32mforget manner.[m
[32m+[m
[32m+[m[32mThere are application concepts (browser, email client, etc) that are common[m
[32m+[m[32macross all platforms, and they may be launched differently on each platform.[m
[32m+[m[32mLaunchy is here to make a common approach to launching external applications from[m
[32m+[m[32mwithin ruby programs.[m
[32m+[m
[