# frozen_string_literal: true

class Floor < ApplicationRecord
  has_many :slots
  validates :number_of_floor, numericality: { only_integer: true, in: 0..10 }, uniqueness: true, presence: true
end
