# frozen_string_literal: true

class User < ApplicationRecord
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable, :trackable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :validatable,
         :trackable, :omniauthable, omniauth_providers: [:google_oauth2]
    
  validates :name, presence: true
  
  has_many :customer_details

  before_update do
    self.name = name.downcase.titleize
  end

  def self.from_omniauth(access_token)
    user = User.where(email: access_token.info.email).first
    user ||= User.create(
                          name: access_token.info.name,
                          email: access_token.info.email,
                          password: Devise.friendly_token[0, 20]
                          )
  
    user
  end

end


