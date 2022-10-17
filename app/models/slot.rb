# frozen_string_literal: true

class Slot < ApplicationRecord
  belongs_to :floor
  has_one :user_detail
end
