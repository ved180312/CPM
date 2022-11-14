# frozen_string_literal: true

class Slot < ApplicationRecord
  belongs_to :floor
  has_one :customer_detail
  validates :slot_number, presence: true
end
