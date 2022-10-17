# frozen_string_literal: true

class UserDetail < ApplicationRecord
  belongs_to :slot

  validates :name, :car_color, presence: true, length: { maximum: 30 }

  validates :in_time, :out_time, presence: true

  validates :car_number, uniqueness: true, presence: true,
                         format: { with: /\A([A-Z]{2})+[0-9]{2}+[A-Z]{2}+[0-9]{4}\z/i }
end
