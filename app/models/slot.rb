# frozen_string_literal: true

class Slot < ApplicationRecord
  belongs_to :floor
  has_one :customer_detail
  validates :slot_number, presence: true

  scope :booked, -> { where(status: Slot::STATUS[:booked]) }
  scope :empty, -> { where(status: Slot::STATUS[:empty]) }

  STATUS = {
    booked: true,
    empty: false
  }

end
