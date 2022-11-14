# frozen_string_literal: true

class AddFloorIdToCustomerDetails < ActiveRecord::Migration[7.0]
  def change
    add_column :customer_details, :floor_id, :int
  end
end
