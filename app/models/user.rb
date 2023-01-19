# frozen_string_literal: true

class User < ApplicationRecord
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable, :trackable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :validatable, :trackable
    
  validates :name, presence: true
  
  has_many :customer_details

  before_update do
    self.name = name.downcase.titleize
  end
end
