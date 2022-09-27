Rails.application.routes.draw do
  # get 'floors/index'
  # get 'floors/new'
  # get 'floors/edit'
  # get 'floors/view'
  # get 'user_details/index'
  # get 'user_details/show'
  # get 'user_details/new'
  # get 'user_details/edit'
  # get 'homes/index'

  
  devise_for :users, controllers: {
    sessions: 'users/sessions'
  }

  root to: "homes#index"

  resources :user_details
  resources :floors

  # Define your application routes per the DSL in https://guides.rubyonrails.org/routing.html

  # Defines the root path route ("/")
  # root "articles#index"
end
