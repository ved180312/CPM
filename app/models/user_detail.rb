# frozen_string_literal: true

# usermodel
class UserDetail < ApplicationRecord
  belongs_to :slot

  validates :name, :car_color, presence: true, length: { maximum: 30 }

  validates :in_time, presence: true

  validates_comparison_of :in_time, greater_than_or_equal_to: Time.now.strftime('%d/%m/%Y %H:%M')

  validates :out_time, comparison: { greater_than: :in_time }, presence: true

  validates :car_number, uniqueness: true, presence: true,
                         format: { with: /\A([A-Z]{2})+[0-9]{2}+[A-Z]{2}+[0-9]{4}\z/i }
end

# validates_comparison_of :in_time, greater_than: Time.now.strftime()
