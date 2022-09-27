class Floor < ApplicationRecord
    has_many :user_details
    validates :number_of_floor, numericality: { only_integer: true , :greater_than_or_equal_to => 0, :less_than_or_equal_to => 10} , uniqueness: true 
end
