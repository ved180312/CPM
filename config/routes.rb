# frozen_string_literal: true

Rails.application.routes.draw do

  get 'customer_details/new/:id', to: 'customer_details#new', as: 'new_customer_details'
  get 'homes/hello'
  get 'homes/cpm'
  root to: 'homes#index'

  devise_for :users, controllers: {
    sessions: 'users/sessions'
  }
  
  get 'slots/new/:id', to: 'slots#new', as: 'new_slot'
  
  resources :slots do
    collection do
      get 'booked_slot', to: 'slots#booked_slot'
      get 'empty_slot' => 'slots#empty_slot'
    end

    # member do
    #   get 'new/:id', to: 'slots#new', as: 'new_slot'
    # end
  end

  resources :customer_details, except: %i[new]

  resources :floors do
  end
  get 'floors/booked_floor/:id' => 'floors#booked_floor', as: 'booked_floor_slots'
  get 'floors/empty_floor/:id' => 'floors#empty_floor', as: 'empty_floor_slots'

end
