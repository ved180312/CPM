# frozen_string_literal: true

class RemoveFloorIdFromCustomerDetails < ActiveRecord::Migration[7.0]
  def change
    remove_column :customer_details, :floor_id, :integer
  end
end
