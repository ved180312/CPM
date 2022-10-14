# frozen_string_literal: true

Rails.application.routes.draw do
  # get 'slots/index'
  # get 'slots/edit'
  get 'slots/new/:id', to: 'slots#new', as: 'new_slot'
  # get 'slots/show'
  # get 'floors/index'
  # get 'floors/new'
  # get 'floors/edit'
  # get 'floors/view'
  # get 'user_details/index'
  # get 'user_details/show'
  get 'user_details/new/:id', to: 'user_details#new', as: 'new_user_details'
  # get 'user_details/edit'
  # get 'homes/index'

  devise_for :users, controllers: {
    sessions: 'users/sessions'
  }

  root to: 'homes#index'

  resources :slots, except: %i[new]
  resources :user_details, except: %i[new]
  resources :floors

  # Define your application routes per the DSL in https://guides.rubyonrails.org/routing.html

  # Defines the root path route ("/")
  # root "articles#index"
end
