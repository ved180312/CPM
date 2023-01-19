# frozen_string_literal: true

# usermodel
class CustomerDetail < ApplicationRecord
  belongs_to :slot
  belongs_to :user
  
  before_create do 
    self.car_color = car_color.downcase.titleize
    self.car_number = car_number.upcase
  end

  validates :name, :car_color, presence: true, length: { maximum: 30 }

  validates :in_time, presence: true

  validates_comparison_of :in_time, greater_than_or_equal_to: Time.now.strftime('%d/%m/%Y %H:%M')

  validates :out_time, comparison: { greater_than: :in_time }, presence: true

  validates :car_number, uniqueness: true, presence: true,
                         format: { with: /\A([A-Z]{2})+[0-9]{2}+[A-Z]{2}+[0-9]{4}\z/i }


end
